use egml::model::base::Reference;

#[derive(Debug, Clone, PartialEq, Default)]
pub struct AbstractCityObjectReference(Reference);

impl From<Reference> for AbstractCityObjectReference {
    fn from(reference: Reference) -> Self {
        Self(reference)
    }
}

impl From<AbstractCityObjectReference> for Reference {
    fn from(reference: AbstractCityObjectReference) -> Self {
        reference.0
    }
}

impl From<&AbstractCityObjectReference> for Reference {
    fn from(reference: &AbstractCityObjectReference) -> Self {
        reference.0.clone()
    }
}
