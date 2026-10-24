use crate::impl_abstract_unoccupied_space_mut_traits;
use crate::impl_abstract_unoccupied_space_traits;
use crate::model::building::values::{
    BuildingRoomClassValue, BuildingRoomFunctionValue, BuildingRoomUsageValue,
};
use crate::model::building::{BuildingFurnitureProperty, RoomHeight};
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
pub struct BuildingRoom {
    pub(crate) abstract_unoccupied_space: AbstractUnoccupiedSpace,
    class: Option<BuildingRoomClassValue>,
    functions: Vec<BuildingRoomFunctionValue>,
    usages: Vec<BuildingRoomUsageValue>,
    room_heights: Vec<RoomHeight>,
    building_furniture: Vec<BuildingFurnitureProperty>,
}

impl BuildingRoom {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_unoccupied_space(AbstractUnoccupiedSpace::new(id))
    }

    pub fn from_abstract_unoccupied_space(
        abstract_unoccupied_space: AbstractUnoccupiedSpace,
    ) -> Self {
        BuildingRoom {
            abstract_unoccupied_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            room_heights: Vec::new(),
            building_furniture: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&BuildingRoomClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: BuildingRoomClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<BuildingRoomClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[BuildingRoomFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [BuildingRoomFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<BuildingRoomFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: BuildingRoomFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = BuildingRoomFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[BuildingRoomUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [BuildingRoomUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<BuildingRoomUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: BuildingRoomUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = BuildingRoomUsageValue>) {
        self.usages.extend(usages);
    }

    pub fn room_heights(&self) -> &[RoomHeight] {
        &self.room_heights
    }

    pub fn room_heights_mut(&mut self) -> &mut [RoomHeight] {
        &mut self.room_heights
    }

    pub fn set_room_heights(&mut self, room_heights: Vec<RoomHeight>) {
        self.room_heights = room_heights;
    }

    pub fn push_room_height(&mut self, room_height: RoomHeight) {
        self.room_heights.push(room_height);
    }

    pub fn extend_room_heights(&mut self, room_heights: impl IntoIterator<Item = RoomHeight>) {
        self.room_heights.extend(room_heights);
    }

    pub fn building_furniture(&self) -> &[BuildingFurnitureProperty] {
        &self.building_furniture
    }

    pub fn building_furniture_mut(&mut self) -> &mut [BuildingFurnitureProperty] {
        &mut self.building_furniture
    }

    pub fn set_building_furniture(&mut self, building_furniture: Vec<BuildingFurnitureProperty>) {
        self.building_furniture = building_furniture;
    }

    pub fn push_building_furniture(&mut self, building_furniture: BuildingFurnitureProperty) {
        self.building_furniture.push(building_furniture);
    }

    pub fn extend_building_furniture(
        &mut self,
        building_furniture: impl IntoIterator<Item = BuildingFurnitureProperty>,
    ) {
        self.building_furniture.extend(building_furniture);
    }
}

impl AsAbstractUnoccupiedSpace for BuildingRoom {
    fn abstract_unoccupied_space(&self) -> &AbstractUnoccupiedSpace {
        &self.abstract_unoccupied_space
    }
}

impl AsAbstractUnoccupiedSpaceMut for BuildingRoom {
    fn abstract_unoccupied_space_mut(&mut self) -> &mut AbstractUnoccupiedSpace {
        &mut self.abstract_unoccupied_space
    }
}

impl_abstract_unoccupied_space_traits!(BuildingRoom);
impl_abstract_unoccupied_space_mut_traits!(BuildingRoom);
crate::impl_has_feature_type!(BuildingRoom, BuildingRoom);

impl IterFeatures for BuildingRoom {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into())
                .chain(self.abstract_unoccupied_space.iter_features())
                .chain(
                    self.building_furniture
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for BuildingRoom {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_unoccupied_space.for_each_feature_mut(f);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for BuildingRoom {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_unoccupied_space.compute_envelope()
    }
}

impl ApplyTransform for BuildingRoom {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_unoccupied_space.apply_transform(m);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_unoccupied_space.apply_isometry(isometry);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_unoccupied_space.apply_translation(vector);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_unoccupied_space.apply_rotation(rotation);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_unoccupied_space.apply_scale(scale);

        for prop in &mut self.building_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::construction::enums::HeightStatusValue;
    use egml::model::basic_types::Code;
    use egml::model::measures::Length;

    fn room_height(value: f64) -> RoomHeight {
        RoomHeight::new(
            Code::new("ceiling").into(),
            Code::new("floor").into(),
            HeightStatusValue::Measured,
            Length::new(value, "m"),
        )
    }

    #[test]
    fn test_room_heights_accessors() {
        let mut building_room = BuildingRoom::new(Id::try_from("room").expect("valid id"));
        assert!(building_room.room_heights().is_empty());

        building_room.push_room_height(room_height(2.5));
        building_room.extend_room_heights([room_height(2.75)]);
        assert_eq!(building_room.room_heights().len(), 2);

        building_room.set_room_heights(vec![room_height(3.0)]);
        assert_eq!(building_room.room_heights(), &[room_height(3.0)]);
    }
}
