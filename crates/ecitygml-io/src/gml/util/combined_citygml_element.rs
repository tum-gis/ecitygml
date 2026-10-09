use crate::Error;
use crate::gml::util::CityGmlElement;
use egml::io::util::{GmlElement, XalElement, XmlDocumentIndex, XmlElement};
use tracing::warn;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum CombinedCityGmlElement {
    CityGml(CityGmlElement),
    Gml(GmlElement),
    Xal(XalElement),
}

impl XmlElement for CombinedCityGmlElement {
    fn from_local_name(local_name: &str) -> Option<Self> {
        CityGmlElement::from_local_name(local_name)
            .map(Self::CityGml)
            .or_else(|| GmlElement::from_local_name(local_name).map(Self::Gml))
            .or_else(|| XalElement::from_local_name(local_name).map(Self::Xal))
    }

    fn local_name(&self) -> &'static str {
        match self {
            Self::CityGml(e) => e.local_name(),
            Self::Gml(e) => e.local_name(),
            Self::Xal(e) => e.local_name(),
        }
    }
}

impl From<CityGmlElement> for CombinedCityGmlElement {
    fn from(e: CityGmlElement) -> Self {
        Self::CityGml(e)
    }
}

impl From<GmlElement> for CombinedCityGmlElement {
    fn from(e: GmlElement) -> Self {
        Self::Gml(e)
    }
}

impl From<XalElement> for CombinedCityGmlElement {
    fn from(e: XalElement) -> Self {
        Self::Xal(e)
    }
}

pub fn collect_gml_child<T>(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    element: CombinedCityGmlElement,
    config: &egml::io::util::DeserializationConfig,
    deserializer: fn(
        &[u8],
        &XmlDocumentIndex<GmlElement>,
        &egml::io::util::DeserializationConfig,
    ) -> Result<T, egml::io::Error>,
) -> Result<Option<T>, Error> {
    let all_matches = index.get(element);
    match all_matches.first() {
        None => Ok(None),
        Some(child) => {
            let slice = &xml_document[child.range()];
            let filtered_child = child.convert(|e| match e {
                CombinedCityGmlElement::Gml(g) => Some(g),
                _ => None,
            });
            deserializer(slice, &filtered_child, config)
                .map(Some)
                .map_err(Error::from)
        }
    }
}

pub fn collect_xal_child<T>(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    element: CombinedCityGmlElement,
    config: &egml::io::util::DeserializationConfig,
    deserializer: fn(
        &[u8],
        &XmlDocumentIndex<XalElement>,
        &egml::io::util::DeserializationConfig,
    ) -> Result<T, egml::io::Error>,
) -> Result<Option<T>, Error> {
    let all_matches = index.get(element);
    match all_matches.first() {
        None => Ok(None),
        Some(child) => {
            let slice = &xml_document[child.range()];
            let filtered_child = child.convert(|e| match e {
                CombinedCityGmlElement::Xal(x) => Some(x),
                _ => None,
            });
            deserializer(slice, &filtered_child, config)
                .map(Some)
                .map_err(Error::from)
        }
    }
}

/// Like [`collect_gml_child`], but never fails: a child element that is present yet fails to
/// deserialize (e.g. a `gml:MultiSurface` with zero `surfaceMember`s, invalid per OGC 07-036
/// §11.3.4.1) is dropped and logged instead of failing the feature that carries it. Use this for
/// optional LOD geometry representations, where losing one representation shouldn't sink the
/// whole feature; keep [`collect_gml_child`] for properties the feature can't meaningfully exist
/// without.
pub fn collect_gml_child_lenient<T>(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    element: CombinedCityGmlElement,
    config: &egml::io::util::DeserializationConfig,
    deserializer: fn(
        &[u8],
        &XmlDocumentIndex<GmlElement>,
        &egml::io::util::DeserializationConfig,
    ) -> Result<T, egml::io::Error>,
) -> Option<T> {
    match collect_gml_child(xml_document, index, element, config, deserializer) {
        Ok(value) => value,
        Err(error) => {
            warn!(?element, ?error, "dropping invalid geometry property");
            None
        }
    }
}
