use crate::impl_abstract_unoccupied_space_mut_traits;
use crate::impl_abstract_unoccupied_space_traits;
use crate::model::bridge::BridgeFurnitureProperty;
use crate::model::bridge::values::{
    BridgeRoomClassValue, BridgeRoomFunctionValue, BridgeRoomUsageValue,
};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{
    AbstractUnoccupiedSpace, AsAbstractUnoccupiedSpace, AsAbstractUnoccupiedSpaceMut,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct BridgeRoom {
    pub(crate) abstract_unoccupied_space: AbstractUnoccupiedSpace,
    class: Option<BridgeRoomClassValue>,
    functions: Vec<BridgeRoomFunctionValue>,
    usages: Vec<BridgeRoomUsageValue>,
    bridge_furniture: Vec<BridgeFurnitureProperty>,
}

impl BridgeRoom {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_unoccupied_space(AbstractUnoccupiedSpace::new(id))
    }

    pub fn from_abstract_unoccupied_space(
        abstract_unoccupied_space: AbstractUnoccupiedSpace,
    ) -> Self {
        BridgeRoom {
            abstract_unoccupied_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            bridge_furniture: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&BridgeRoomClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: BridgeRoomClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<BridgeRoomClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[BridgeRoomFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [BridgeRoomFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<BridgeRoomFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: BridgeRoomFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = BridgeRoomFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[BridgeRoomUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [BridgeRoomUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<BridgeRoomUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: BridgeRoomUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = BridgeRoomUsageValue>) {
        self.usages.extend(usages);
    }

    pub fn bridge_furniture(&self) -> &[BridgeFurnitureProperty] {
        &self.bridge_furniture
    }

    pub fn bridge_furniture_mut(&mut self) -> &mut [BridgeFurnitureProperty] {
        &mut self.bridge_furniture
    }

    pub fn set_bridge_furniture(&mut self, bridge_furniture: Vec<BridgeFurnitureProperty>) {
        self.bridge_furniture = bridge_furniture;
    }

    pub fn push_bridge_furniture(&mut self, bridge_furniture: BridgeFurnitureProperty) {
        self.bridge_furniture.push(bridge_furniture);
    }

    pub fn extend_bridge_furniture(
        &mut self,
        bridge_furniture: impl IntoIterator<Item = BridgeFurnitureProperty>,
    ) {
        self.bridge_furniture.extend(bridge_furniture);
    }
}

impl AsAbstractUnoccupiedSpace for BridgeRoom {
    fn abstract_unoccupied_space(&self) -> &AbstractUnoccupiedSpace {
        &self.abstract_unoccupied_space
    }
}

impl AsAbstractUnoccupiedSpaceMut for BridgeRoom {
    fn abstract_unoccupied_space_mut(&mut self) -> &mut AbstractUnoccupiedSpace {
        &mut self.abstract_unoccupied_space
    }
}

impl_abstract_unoccupied_space_traits!(BridgeRoom);
impl_abstract_unoccupied_space_mut_traits!(BridgeRoom);
crate::impl_has_feature_type!(BridgeRoom, BridgeRoom);

impl IterFeatures for BridgeRoom {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into())
                .chain(self.abstract_unoccupied_space.iter_features())
                .chain(
                    self.bridge_furniture
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for BridgeRoom {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_unoccupied_space.for_each_feature_mut(f);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for BridgeRoom {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_unoccupied_space.compute_envelope()
    }
}

impl ApplyTransform for BridgeRoom {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_unoccupied_space.apply_transform(m);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_unoccupied_space.apply_isometry(isometry);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_unoccupied_space.apply_translation(vector);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_unoccupied_space.apply_rotation(rotation);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_unoccupied_space.apply_scale(scale);

        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::core::AbstractUnoccupiedSpaceKind;

    fn bridge_room() -> BridgeRoom {
        BridgeRoom::new(Id::try_from("bridge_room").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(bridge_room().feature_type(), FeatureType::BridgeRoom);
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = bridge_room()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::BridgeRoom]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        bridge_room().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::BridgeRoom]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_unoccupied_space_kind() {
        let kind: AbstractUnoccupiedSpaceKind = bridge_room().into();
        assert_eq!(kind.feature_type(), FeatureType::BridgeRoom);

        let round_tripped = BridgeRoom::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, bridge_room());
    }
}
