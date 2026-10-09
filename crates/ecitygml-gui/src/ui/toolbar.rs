#![allow(deprecated)]
use crate::app::AppState;
use std::path::PathBuf;
use three_d::egui::{self, Context};

pub struct ToolbarAction {
    pub open_file: Option<PathBuf>,
    pub recenter: bool,
    pub screenshot: bool,
    pub toggle_sidebar: bool,
    pub toggle_inspector: bool,
}

pub fn show(ctx: &Context, state: &AppState) -> ToolbarAction {
    let mut action = ToolbarAction {
        open_file: None,
        recenter: false,
        screenshot: false,
        toggle_sidebar: false,
        toggle_inspector: false,
    };

    egui::Panel::top("toolbar").show(ctx, |ui| {
        ui.horizontal(|ui| {
            if ui.button("Open File…").clicked()
                && let Some(path) = rfd::FileDialog::new()
                    .add_filter("CityGML", &["gml", "xml", "zst", "gz"])
                    .pick_file()
            {
                action.open_file = Some(path);
            }

            ui.menu_button("View", |ui| {
                let mut show_sidebar = state.show_sidebar;
                if ui.checkbox(&mut show_sidebar, "Sidebar").changed() {
                    action.toggle_sidebar = true;
                }
                let mut show_inspector = state.show_inspector;
                if ui.checkbox(&mut show_inspector, "Inspector").changed() {
                    action.toggle_inspector = true;
                }
            });

            ui.separator();

            if state.is_loading() {
                ui.spinner();
                ui.label("Loading…");
            } else if state.graphics.is_some() {
                let count = state.feature_count;
                let city_object_count = state.city_object_count;
                ui.label(format!(
                    "{count} features · {city_object_count} city objects"
                ));
            }

            if let crate::app::LoadState::Error(msg) = &state.load_state {
                ui.colored_label(egui::Color32::RED, format!("Error: {msg}"));
            }

            match &state.screenshot_status {
                Some(crate::app::ScreenshotStatus::Saved(path)) => {
                    ui.colored_label(
                        egui::Color32::DARK_GREEN,
                        format!("Saved screenshot to {}", path.display()),
                    );
                }
                Some(crate::app::ScreenshotStatus::Error(msg)) => {
                    ui.colored_label(egui::Color32::RED, format!("Screenshot failed: {msg}"));
                }
                None => {}
            }

            // Placed last so it only claims the leftover space to the right of
            // the widgets above, rather than the whole row's width.
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                if ui
                    .add_enabled(state.graphics.is_some(), egui::Button::new("Recenter View"))
                    .on_hover_text("Reset the camera to frame the whole model")
                    .clicked()
                {
                    action.recenter = true;
                }

                if ui
                    .add_enabled(state.graphics.is_some(), egui::Button::new("Screenshot"))
                    .on_hover_text("Save a PNG screenshot of the 3D view")
                    .clicked()
                {
                    action.screenshot = true;
                }
            });
        });
    });

    action
}
