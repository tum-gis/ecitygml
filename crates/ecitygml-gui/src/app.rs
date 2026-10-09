use ecitygml_core::model::common::{FeatureType, HasFeatureType};
use ecitygml_core::store::CityModelGraphicsStore;
use egml::model::base::Id;
use std::collections::HashSet;
use std::path::PathBuf;
use std::sync::Arc;
use std::sync::mpsc::{self, Receiver, Sender};

/// Outcome of the most recent screenshot save attempt, shown in the toolbar.
pub enum ScreenshotStatus {
    Saved(PathBuf),
    Error(String),
}

pub enum LoadResult {
    Ok(CityModelGraphicsStore),
    Err(String),
}

#[derive(Default)]
pub enum LoadState {
    #[default]
    Idle,
    Loading(Receiver<LoadResult>),
    Loaded,
    Error(String),
}

pub struct AppState {
    pub graphics: Option<Arc<CityModelGraphicsStore>>,
    /// Cached once on load (rather than recomputed by walking the arena every frame) since the
    /// toolbar redraws this count on every frame.
    pub feature_count: usize,
    /// Count of city objects (a subset of `feature_count` — excludes non-city-object features
    /// such as appearances). Cached alongside `feature_count` for the same reason.
    pub city_object_count: usize,
    pub selected_id: Option<Id>,
    pub load_state: LoadState,
    pub hidden_feature_types: HashSet<FeatureType>,
    pub screenshot_status: Option<ScreenshotStatus>,
    pub show_sidebar: bool,
    pub show_inspector: bool,
}

impl Default for AppState {
    fn default() -> Self {
        Self {
            graphics: None,
            feature_count: 0,
            city_object_count: 0,
            selected_id: None,
            load_state: LoadState::default(),
            hidden_feature_types: HashSet::new(),
            screenshot_status: None,
            show_sidebar: true,
            show_inspector: true,
        }
    }
}

impl AppState {
    pub fn toggle_feature_type(&mut self, ft: FeatureType) {
        if !self.hidden_feature_types.remove(&ft) {
            self.hidden_feature_types.insert(ft);
        }
    }

    pub fn show_all_feature_types(&mut self) {
        self.hidden_feature_types.clear();
    }

    pub fn hide_all_feature_types(&mut self) {
        if let Some(graphics) = &self.graphics {
            self.hidden_feature_types = graphics
                .city_model_arena
                .iter_features()
                .map(|x| x.feature_type())
                .collect();
        }
    }

    pub fn start_load(&mut self, path: PathBuf) {
        let (tx, rx): (Sender<LoadResult>, Receiver<LoadResult>) = mpsc::channel();
        std::thread::spawn(move || {
            let result = load_store(path);
            let _ = tx.send(result);
        });
        self.load_state = LoadState::Loading(rx);
        self.graphics = None;
        self.selected_id = None;
    }

    /// Returns `true` if the store was newly set (caller should rebuild scene).
    pub fn poll_load(&mut self) -> bool {
        let result = match &self.load_state {
            LoadState::Loading(rx) => rx.try_recv().ok(),
            _ => None,
        };
        match result {
            Some(LoadResult::Ok(graphics)) => {
                self.feature_count = graphics.city_model_arena.iter_features().count();
                self.city_object_count = graphics.city_model_arena.iter_city_objects().count();
                self.graphics = Some(Arc::new(graphics));
                self.load_state = LoadState::Loaded;
                true
            }
            Some(LoadResult::Err(e)) => {
                self.load_state = LoadState::Error(e);
                false
            }
            None => false,
        }
    }

    pub fn is_loading(&self) -> bool {
        matches!(self.load_state, LoadState::Loading(_))
    }
}

fn load_store(path: PathBuf) -> LoadResult {
    use ecitygml::io::GmlReader;

    let result = GmlReader::from_path(&path).and_then(|r| r.finish());
    match result {
        Ok(model) => match CityModelGraphicsStore::from_city_model(model) {
            Ok(graphics) => LoadResult::Ok(graphics),
            Err(e) => LoadResult::Err(e.to_string()),
        },
        Err(e) => LoadResult::Err(e.to_string()),
    }
}
