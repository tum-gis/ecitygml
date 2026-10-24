use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{AbstractLogicalSpace, AsAbstractLogicalSpace, AsAbstractLogicalSpaceMut};
use crate::model::generics::values::{
    GenericLogicalSpaceClassValue, GenericLogicalSpaceFunctionValue, GenericLogicalSpaceUsageValue,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct GenericLogicalSpace {
    pub(crate) abstract_logical_space: AbstractLogicalSpace,
    class: Option<GenericLogicalSpaceClassValue>,
    functions: Vec<GenericLogicalSpaceFunctionValue>,
    usages: Vec<GenericLogicalSpaceUsageValue>,
}

impl GenericLogicalSpace {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_logical_space(AbstractLogicalSpace::new(id))
    }

    pub fn from_abstract_logical_space(abstract_logical_space: AbstractLogicalSpace) -> Self {
        Self {
            abstract_logical_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&GenericLogicalSpaceClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: GenericLogicalSpaceClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<GenericLogicalSpaceClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[GenericLogicalSpaceFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [GenericLogicalSpaceFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<GenericLogicalSpaceFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: GenericLogicalSpaceFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = GenericLogicalSpaceFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[GenericLogicalSpaceUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [GenericLogicalSpaceUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<GenericLogicalSpaceUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: GenericLogicalSpaceUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(
        &mut self,
        usages: impl IntoIterator<Item = GenericLogicalSpaceUsageValue>,
    ) {
        self.usages.extend(usages);
    }
}

impl AsAbstractLogicalSpace for GenericLogicalSpace {
    fn abstract_logical_space(&self) -> &AbstractLogicalSpace {
        &self.abstract_logical_space
    }
}

impl AsAbstractLogicalSpaceMut for GenericLogicalSpace {
    fn abstract_logical_space_mut(&mut self) -> &mut AbstractLogicalSpace {
        &mut self.abstract_logical_space
    }
}

crate::impl_abstract_logical_space_traits!(GenericLogicalSpace);
crate::impl_abstract_logical_space_mut_traits!(GenericLogicalSpace);
crate::impl_has_feature_type!(GenericLogicalSpace, GenericLogicalSpace);

impl IterFeatures for GenericLogicalSpace {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_logical_space.iter_features()))
    }
}

impl ForEachFeatureMut for GenericLogicalSpace {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_logical_space.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for GenericLogicalSpace {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_logical_space.compute_envelope()
    }
}

impl ApplyTransform for GenericLogicalSpace {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_logical_space.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_logical_space.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_logical_space.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_logical_space.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_logical_space.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::core::AbstractLogicalSpaceKind;

    fn generic_logical_space() -> GenericLogicalSpace {
        GenericLogicalSpace::new(Id::try_from("generic_logical_space").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(
            generic_logical_space().feature_type(),
            FeatureType::GenericLogicalSpace
        );
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = generic_logical_space()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::GenericLogicalSpace]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        generic_logical_space().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::GenericLogicalSpace]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_logical_space_kind() {
        let kind: AbstractLogicalSpaceKind = generic_logical_space().into();
        assert_eq!(kind.feature_type(), FeatureType::GenericLogicalSpace);

        let round_tripped = GenericLogicalSpace::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, generic_logical_space());
    }
}
