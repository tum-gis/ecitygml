use crate::model::building::values::{
    BuildingFurnitureClassValue, BuildingFurnitureFunctionValue, BuildingFurnitureUsageValue,
};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::construction::{AbstractFurniture, AsAbstractFurniture, AsAbstractFurnitureMut};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct BuildingFurniture {
    pub(crate) abstract_furniture: AbstractFurniture,
    class: Option<BuildingFurnitureClassValue>,
    functions: Vec<BuildingFurnitureFunctionValue>,
    usages: Vec<BuildingFurnitureUsageValue>,
}

impl BuildingFurniture {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_furniture(AbstractFurniture::new(id))
    }

    pub fn from_abstract_furniture(abstract_furniture: AbstractFurniture) -> Self {
        Self {
            abstract_furniture,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&BuildingFurnitureClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: BuildingFurnitureClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<BuildingFurnitureClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[BuildingFurnitureFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [BuildingFurnitureFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<BuildingFurnitureFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: BuildingFurnitureFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = BuildingFurnitureFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[BuildingFurnitureUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [BuildingFurnitureUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<BuildingFurnitureUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: BuildingFurnitureUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = BuildingFurnitureUsageValue>) {
        self.usages.extend(usages);
    }
}

impl AsAbstractFurniture for BuildingFurniture {
    fn abstract_furniture(&self) -> &AbstractFurniture {
        &self.abstract_furniture
    }
}

impl AsAbstractFurnitureMut for BuildingFurniture {
    fn abstract_furniture_mut(&mut self) -> &mut AbstractFurniture {
        &mut self.abstract_furniture
    }
}

crate::impl_abstract_furniture_traits!(BuildingFurniture);
crate::impl_abstract_furniture_mut_traits!(BuildingFurniture);
crate::impl_has_feature_type!(BuildingFurniture, BuildingFurniture);

impl IterFeatures for BuildingFurniture {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_furniture.iter_features()))
    }
}

impl ForEachFeatureMut for BuildingFurniture {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_furniture.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for BuildingFurniture {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_furniture.compute_envelope()
    }
}

impl ApplyTransform for BuildingFurniture {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_furniture.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_furniture.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_furniture.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_furniture.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_furniture.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::construction::AbstractFurnitureKind;
    use crate::model::core::AbstractOccupiedSpaceKind;

    fn building_furniture() -> BuildingFurniture {
        BuildingFurniture::new(Id::try_from("building_furniture").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(
            building_furniture().feature_type(),
            FeatureType::BuildingFurniture
        );
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = building_furniture()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::BuildingFurniture]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        building_furniture().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::BuildingFurniture]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_furniture_kind() {
        let kind: AbstractFurnitureKind = building_furniture().into();
        assert_eq!(kind.feature_type(), FeatureType::BuildingFurniture);

        let round_tripped = BuildingFurniture::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, building_furniture());
    }

    #[test]
    fn test_converts_to_and_from_abstract_occupied_space_kind() {
        let kind: AbstractOccupiedSpaceKind = building_furniture().into();
        assert!(matches!(
            kind,
            AbstractOccupiedSpaceKind::AbstractFurnitureKind(_)
        ));
        assert_eq!(kind.feature_type(), FeatureType::BuildingFurniture);

        let round_tripped = BuildingFurniture::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, building_furniture());
    }
}
