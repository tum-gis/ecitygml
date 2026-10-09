/// Tuning knobs for deserialization, set once via [`GmlReader::with_config`](crate::gml::GmlReader::with_config)
/// before parsing starts. Process-wide, like [`deserializer_pool`](super::deserializer_pool) —
/// not safe to vary between concurrent `finish()` calls in the same process.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct DeserializationConfig {
    /// `max_depth` for the single-threaded root scan in `deserialize_city_model`.
    initial_scan_depth: Option<usize>,
    /// `max_depth` used when a parallelized CityGML feature deserializer rescans
    /// a truncated index.
    feature_rescan_depth: Option<usize>,
    gml_config: egml::io::util::DeserializationConfig,
}

impl Default for DeserializationConfig {
    fn default() -> Self {
        Self {
            initial_scan_depth: Some(4),
            feature_rescan_depth: Some(5),
            gml_config: egml::io::util::DeserializationConfig::default(),
        }
    }
}

impl DeserializationConfig {
    pub fn initial_scan_depth(&self) -> Option<usize> {
        self.initial_scan_depth
    }

    pub fn set_initial_scan_depth(&mut self, initial_scan_depth: Option<usize>) {
        self.initial_scan_depth = initial_scan_depth;
    }

    pub fn feature_rescan_depth(&self) -> Option<usize> {
        self.feature_rescan_depth
    }

    pub fn set_feature_rescan_depth(&mut self, feature_rescan_depth: Option<usize>) {
        self.feature_rescan_depth = feature_rescan_depth;
    }

    pub fn gml_config(&self) -> &egml::io::util::DeserializationConfig {
        &self.gml_config
    }

    pub fn set_gml_config(&mut self, gml_config: egml::io::util::DeserializationConfig) {
        self.gml_config = gml_config;
    }
}
