use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::construction::values::{
    OtherConstructionClassValue, OtherConstructionFunctionValue, OtherConstructionUsageValue,
};
use crate::model::construction::{
    AbstractConstruction, AsAbstractConstruction, AsAbstractConstructionMut,
};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct OtherConstruction {
    pub(crate) abstract_construction: AbstractConstruction,
    class: Option<OtherConstructionClassValue>,
    functions: Vec<OtherConstructionFunctionValue>,
    usages: Vec<OtherConstructionUsageValue>,
}

impl OtherConstruction {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_construction(AbstractConstruction::new(id))
    }

    pub fn from_abstract_construction(abstract_construction: AbstractConstruction) -> Self {
        Self {
            abstract_construction,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&OtherConstructionClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: OtherConstructionClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<OtherConstructionClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[OtherConstructionFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [OtherConstructionFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<OtherConstructionFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: OtherConstructionFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = OtherConstructionFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[OtherConstructionUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [OtherConstructionUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<OtherConstructionUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: OtherConstructionUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = OtherConstructionUsageValue>) {
        self.usages.extend(usages);
    }
}

impl AsAbstractConstruction for OtherConstruction {
    fn abstract_construction(&self) -> &AbstractConstruction {
        &self.abstract_construction
    }
}

impl AsAbstractConstructionMut for OtherConstruction {
    fn abstract_construction_mut(&mut self) -> &mut AbstractConstruction {
        &mut self.abstract_construction
    }
}

crate::impl_abstract_construction_traits!(OtherConstruction);
crate::impl_abstract_construction_mut_traits!(OtherConstruction);
crate::impl_has_feature_type!(OtherConstruction, OtherConstruction);

impl IterFeatures for OtherConstruction {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_construction.iter_features()))
    }
}

impl ForEachFeatureMut for OtherConstruction {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_construction.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for OtherConstruction {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_construction.compute_envelope()
    }
}

impl ApplyTransform for OtherConstruction {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_construction.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_construction.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_construction.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_construction.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_construction.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::construction::AbstractConstructionKind;
    use crate::model::core::AbstractOccupiedSpaceKind;

    fn other_construction() -> OtherConstruction {
        OtherConstruction::new(Id::try_from("other_construction").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(
            other_construction().feature_type(),
            FeatureType::OtherConstruction
        );
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = other_construction()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::OtherConstruction]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        other_construction().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::OtherConstruction]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_construction_kind() {
        let kind: AbstractConstructionKind = other_construction().into();
        assert!(matches!(
            kind,
            AbstractConstructionKind::OtherConstruction(_)
        ));
        assert_eq!(kind.feature_type(), FeatureType::OtherConstruction);

        let round_tripped = OtherConstruction::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, other_construction());
    }

    #[test]
    fn test_converts_to_and_from_abstract_occupied_space_kind() {
        let kind: AbstractOccupiedSpaceKind = other_construction().into();
        assert_eq!(kind.feature_type(), FeatureType::OtherConstruction);

        let round_tripped = OtherConstruction::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, other_construction());
    }
}
