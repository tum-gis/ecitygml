use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{
    AbstractUnoccupiedSpace, AsAbstractUnoccupiedSpace, AsAbstractUnoccupiedSpaceMut,
};
use crate::model::generics::values::{
    GenericUnoccupiedSpaceClassValue, GenericUnoccupiedSpaceFunctionValue,
    GenericUnoccupiedSpaceUsageValue,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct GenericUnoccupiedSpace {
    pub(crate) abstract_unoccupied_space: AbstractUnoccupiedSpace,
    class: Option<GenericUnoccupiedSpaceClassValue>,
    functions: Vec<GenericUnoccupiedSpaceFunctionValue>,
    usages: Vec<GenericUnoccupiedSpaceUsageValue>,
}

impl GenericUnoccupiedSpace {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_unoccupied_space(AbstractUnoccupiedSpace::new(id))
    }

    pub fn from_abstract_unoccupied_space(
        abstract_unoccupied_space: AbstractUnoccupiedSpace,
    ) -> Self {
        Self {
            abstract_unoccupied_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&GenericUnoccupiedSpaceClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: GenericUnoccupiedSpaceClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<GenericUnoccupiedSpaceClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[GenericUnoccupiedSpaceFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [GenericUnoccupiedSpaceFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<GenericUnoccupiedSpaceFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: GenericUnoccupiedSpaceFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = GenericUnoccupiedSpaceFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[GenericUnoccupiedSpaceUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [GenericUnoccupiedSpaceUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<GenericUnoccupiedSpaceUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: GenericUnoccupiedSpaceUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(
        &mut self,
        usages: impl IntoIterator<Item = GenericUnoccupiedSpaceUsageValue>,
    ) {
        self.usages.extend(usages);
    }
}

impl AsAbstractUnoccupiedSpace for GenericUnoccupiedSpace {
    fn abstract_unoccupied_space(&self) -> &AbstractUnoccupiedSpace {
        &self.abstract_unoccupied_space
    }
}

impl AsAbstractUnoccupiedSpaceMut for GenericUnoccupiedSpace {
    fn abstract_unoccupied_space_mut(&mut self) -> &mut AbstractUnoccupiedSpace {
        &mut self.abstract_unoccupied_space
    }
}

crate::impl_abstract_unoccupied_space_traits!(GenericUnoccupiedSpace);
crate::impl_abstract_unoccupied_space_mut_traits!(GenericUnoccupiedSpace);
crate::impl_has_feature_type!(GenericUnoccupiedSpace, GenericUnoccupiedSpace);

impl IterFeatures for GenericUnoccupiedSpace {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_unoccupied_space.iter_features()))
    }
}

impl ForEachFeatureMut for GenericUnoccupiedSpace {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_unoccupied_space.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for GenericUnoccupiedSpace {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_unoccupied_space.compute_envelope()
    }
}

impl ApplyTransform for GenericUnoccupiedSpace {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_unoccupied_space.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_unoccupied_space.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_unoccupied_space.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_unoccupied_space.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_unoccupied_space.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::core::AbstractUnoccupiedSpaceKind;

    fn generic_unoccupied_space() -> GenericUnoccupiedSpace {
        GenericUnoccupiedSpace::new(Id::try_from("generic_unoccupied_space").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(
            generic_unoccupied_space().feature_type(),
            FeatureType::GenericUnoccupiedSpace
        );
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = generic_unoccupied_space()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::GenericUnoccupiedSpace]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        generic_unoccupied_space()
            .for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::GenericUnoccupiedSpace]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_unoccupied_space_kind() {
        let kind: AbstractUnoccupiedSpaceKind = generic_unoccupied_space().into();
        assert_eq!(kind.feature_type(), FeatureType::GenericUnoccupiedSpace);

        let round_tripped = GenericUnoccupiedSpace::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, generic_unoccupied_space());
    }
}
