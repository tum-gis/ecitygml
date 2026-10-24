use crate::model::bridge::values::{BridgeClassValue, BridgeFunctionValue, BridgeUsageValue};
use crate::model::common::{CodeListValue, ForEachFeatureMut, IterFeatures};
use crate::model::construction::{
    AbstractConstruction, AsAbstractConstruction, AsAbstractConstructionMut,
};

use crate::model::bridge::{
    BridgeConstructiveElementProperty, BridgeFurnitureProperty, BridgeInstallationProperty,
    BridgeRoomProperty,
};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct AbstractBridge {
    pub(crate) abstract_construction: AbstractConstruction,
    class: Option<BridgeClassValue>,
    functions: Vec<BridgeFunctionValue>,
    usages: Vec<BridgeUsageValue>,
    is_movable: Option<bool>,
    bridge_installations: Vec<BridgeInstallationProperty>,
    bridge_constructive_elements: Vec<BridgeConstructiveElementProperty>,
    bridge_rooms: Vec<BridgeRoomProperty>,
    bridge_furniture: Vec<BridgeFurnitureProperty>,
}

impl AbstractBridge {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_construction(AbstractConstruction::new(id))
    }

    pub fn from_abstract_construction(abstract_construction: AbstractConstruction) -> Self {
        Self {
            abstract_construction,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            is_movable: None,
            bridge_installations: Vec::new(),
            bridge_constructive_elements: Vec::new(),
            bridge_rooms: Vec::new(),
            bridge_furniture: Vec::new(),
        }
    }
}

pub trait AsAbstractBridge: AsAbstractConstruction {
    fn abstract_bridge(&self) -> &AbstractBridge;

    fn class(&self) -> Option<&BridgeClassValue> {
        self.abstract_bridge().class.as_ref()
    }

    /// Interprets `class` against a specific code list, if its codeSpace
    /// matches (or `class` has no codeSpace at all).
    fn class_as<T: CodeListValue>(&self) -> Option<T> {
        self.class()?.interpret::<T>()
    }

    fn functions(&self) -> &[BridgeFunctionValue] {
        &self.abstract_bridge().functions
    }

    /// Interprets `functions` against a specific code list, yielding only
    /// the entries whose codeSpace matches (or have no codeSpace at all).
    fn functions_as<T: CodeListValue + 'static>(&self) -> impl Iterator<Item = T> + '_ {
        self.functions()
            .iter()
            .filter_map(BridgeFunctionValue::interpret::<T>)
    }

    fn usages(&self) -> &[BridgeUsageValue] {
        &self.abstract_bridge().usages
    }

    /// Interprets `usages` against a specific code list, yielding only
    /// the entries whose codeSpace matches (or have no codeSpace at all).
    fn usages_as<T: CodeListValue + 'static>(&self) -> impl Iterator<Item = T> + '_ {
        self.usages()
            .iter()
            .filter_map(BridgeUsageValue::interpret::<T>)
    }

    fn is_movable(&self) -> Option<bool> {
        self.abstract_bridge().is_movable
    }

    fn bridge_installations(&self) -> &[BridgeInstallationProperty] {
        &self.abstract_bridge().bridge_installations
    }

    fn bridge_constructive_elements(&self) -> &[BridgeConstructiveElementProperty] {
        &self.abstract_bridge().bridge_constructive_elements
    }

    fn bridge_rooms(&self) -> &[BridgeRoomProperty] {
        &self.abstract_bridge().bridge_rooms
    }

    fn bridge_furniture(&self) -> &[BridgeFurnitureProperty] {
        &self.abstract_bridge().bridge_furniture
    }
}

pub trait AsAbstractBridgeMut: AsAbstractConstructionMut + AsAbstractBridge {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge;

    fn set_class(&mut self, class: BridgeClassValue) {
        self.abstract_bridge_mut().class = Some(class);
    }

    fn set_class_opt(&mut self, class: Option<BridgeClassValue>) {
        self.abstract_bridge_mut().class = class;
    }

    fn clear_class(&mut self) {
        self.abstract_bridge_mut().class = None;
    }

    /// Sets `class`, encoding it with `T`'s code list codeSpace.
    fn set_class_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_bridge_mut().class = Some(BridgeClassValue::from_value(value));
    }

    fn functions_mut(&mut self) -> &mut [BridgeFunctionValue] {
        &mut self.abstract_bridge_mut().functions
    }

    fn set_functions(&mut self, functions: Vec<BridgeFunctionValue>) {
        self.abstract_bridge_mut().functions = functions;
    }

    fn push_function(&mut self, function: BridgeFunctionValue) {
        self.abstract_bridge_mut().functions.push(function);
    }

    fn extend_functions(&mut self, functions: impl IntoIterator<Item = BridgeFunctionValue>) {
        self.abstract_bridge_mut().functions.extend(functions);
    }

    /// Appends a function, encoding it with `T`'s code list codeSpace.
    fn push_function_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_bridge_mut()
            .functions
            .push(BridgeFunctionValue::from_value(value));
    }

    fn usages_mut(&mut self) -> &mut [BridgeUsageValue] {
        &mut self.abstract_bridge_mut().usages
    }

    fn set_usages(&mut self, usages: Vec<BridgeUsageValue>) {
        self.abstract_bridge_mut().usages = usages;
    }

    fn push_usage(&mut self, usage: BridgeUsageValue) {
        self.abstract_bridge_mut().usages.push(usage);
    }

    fn extend_usages(&mut self, usages: impl IntoIterator<Item = BridgeUsageValue>) {
        self.abstract_bridge_mut().usages.extend(usages);
    }

    /// Appends a usage, encoding it with `T`'s code list codeSpace.
    fn push_usage_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_bridge_mut()
            .usages
            .push(BridgeUsageValue::from_value(value));
    }

    fn set_is_movable(&mut self, is_movable: bool) {
        self.abstract_bridge_mut().is_movable = Some(is_movable);
    }

    fn set_is_movable_opt(&mut self, is_movable: Option<bool>) {
        self.abstract_bridge_mut().is_movable = is_movable;
    }

    fn clear_is_movable(&mut self) {
        self.abstract_bridge_mut().is_movable = None;
    }

    fn bridge_installations_mut(&mut self) -> &mut [BridgeInstallationProperty] {
        &mut self.abstract_bridge_mut().bridge_installations
    }

    fn set_bridge_installations(&mut self, bridge_installations: Vec<BridgeInstallationProperty>) {
        self.abstract_bridge_mut().bridge_installations = bridge_installations;
    }

    fn push_bridge_installation(&mut self, installation: BridgeInstallationProperty) {
        self.abstract_bridge_mut()
            .bridge_installations
            .push(installation);
    }

    fn extend_bridge_installations(
        &mut self,
        installations: impl IntoIterator<Item = BridgeInstallationProperty>,
    ) {
        self.abstract_bridge_mut()
            .bridge_installations
            .extend(installations);
    }

    fn bridge_constructive_elements_mut(&mut self) -> &mut [BridgeConstructiveElementProperty] {
        &mut self.abstract_bridge_mut().bridge_constructive_elements
    }

    fn set_bridge_constructive_elements(
        &mut self,
        bridge_constructive_elements: Vec<BridgeConstructiveElementProperty>,
    ) {
        self.abstract_bridge_mut().bridge_constructive_elements = bridge_constructive_elements;
    }

    fn push_bridge_constructive_element(&mut self, element: BridgeConstructiveElementProperty) {
        self.abstract_bridge_mut()
            .bridge_constructive_elements
            .push(element);
    }

    fn extend_bridge_constructive_elements(
        &mut self,
        elements: impl IntoIterator<Item = BridgeConstructiveElementProperty>,
    ) {
        self.abstract_bridge_mut()
            .bridge_constructive_elements
            .extend(elements);
    }

    fn bridge_rooms_mut(&mut self) -> &mut [BridgeRoomProperty] {
        &mut self.abstract_bridge_mut().bridge_rooms
    }

    fn set_bridge_rooms(&mut self, bridge_rooms: Vec<BridgeRoomProperty>) {
        self.abstract_bridge_mut().bridge_rooms = bridge_rooms;
    }

    fn push_bridge_room(&mut self, bridge_room: BridgeRoomProperty) {
        self.abstract_bridge_mut().bridge_rooms.push(bridge_room);
    }

    fn extend_bridge_rooms(&mut self, bridge_rooms: impl IntoIterator<Item = BridgeRoomProperty>) {
        self.abstract_bridge_mut().bridge_rooms.extend(bridge_rooms);
    }

    fn bridge_furniture_mut(&mut self) -> &mut [BridgeFurnitureProperty] {
        &mut self.abstract_bridge_mut().bridge_furniture
    }

    fn set_bridge_furniture(&mut self, bridge_furniture: Vec<BridgeFurnitureProperty>) {
        self.abstract_bridge_mut().bridge_furniture = bridge_furniture;
    }

    fn push_bridge_furniture(&mut self, bridge_furniture: BridgeFurnitureProperty) {
        self.abstract_bridge_mut()
            .bridge_furniture
            .push(bridge_furniture);
    }

    fn extend_bridge_furniture(
        &mut self,
        bridge_furniture: impl IntoIterator<Item = BridgeFurnitureProperty>,
    ) {
        self.abstract_bridge_mut()
            .bridge_furniture
            .extend(bridge_furniture);
    }
}

impl AsAbstractBridge for AbstractBridge {
    fn abstract_bridge(&self) -> &AbstractBridge {
        self
    }
}

impl AsAbstractBridgeMut for AbstractBridge {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge {
        self
    }
}

#[macro_export]
macro_rules! impl_abstract_bridge_traits {
    ($type:ty) => {
        $crate::impl_abstract_construction_traits!($type);

        impl $crate::model::construction::AsAbstractConstruction for $type {
            fn abstract_construction(&self) -> &$crate::model::construction::AbstractConstruction {
                &<$type as $crate::model::bridge::AsAbstractBridge>::abstract_bridge(self)
                    .abstract_construction
            }
        }
    };
}

#[macro_export]
macro_rules! impl_abstract_bridge_mut_traits {
    ($type:ty) => {
        $crate::impl_abstract_construction_mut_traits!($type);

        impl $crate::model::construction::AsAbstractConstructionMut for $type {
            fn abstract_construction_mut(
                &mut self,
            ) -> &mut $crate::model::construction::AbstractConstruction {
                &mut <$type as $crate::model::bridge::AsAbstractBridgeMut>::abstract_bridge_mut(
                    self,
                )
                .abstract_construction
            }
        }
    };
}

impl_abstract_bridge_traits!(AbstractBridge);
impl_abstract_bridge_mut_traits!(AbstractBridge);

impl IterFeatures for AbstractBridge {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            self.abstract_construction
                .iter_features()
                .chain(
                    self.bridge_installations
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.bridge_constructive_elements
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.bridge_rooms
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.bridge_furniture
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for AbstractBridge {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        self.abstract_construction.for_each_feature_mut(f);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for AbstractBridge {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_construction.compute_envelope()
    }
}

impl ApplyTransform for AbstractBridge {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_construction.apply_transform(m);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_construction.apply_isometry(isometry);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_construction.apply_translation(vector);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_construction.apply_rotation(rotation);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_construction.apply_scale(scale);

        for prop in &mut self.bridge_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.bridge_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.bridge_rooms {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.bridge_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}
