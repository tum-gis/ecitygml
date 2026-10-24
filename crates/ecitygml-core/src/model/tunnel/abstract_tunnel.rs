use crate::model::common::{CodeListValue, ForEachFeatureMut, IterFeatures};
use crate::model::construction::{
    AbstractConstruction, AsAbstractConstruction, AsAbstractConstructionMut,
};
use crate::model::tunnel::values::{TunnelClassValue, TunnelFunctionValue, TunnelUsageValue};
use crate::model::tunnel::{
    HollowSpaceProperty, TunnelConstructiveElementProperty, TunnelFurnitureProperty,
    TunnelInstallationProperty,
};

use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct AbstractTunnel {
    pub(crate) abstract_construction: AbstractConstruction,
    class: Option<TunnelClassValue>,
    functions: Vec<TunnelFunctionValue>,
    usages: Vec<TunnelUsageValue>,
    tunnel_installations: Vec<TunnelInstallationProperty>,
    tunnel_constructive_elements: Vec<TunnelConstructiveElementProperty>,
    hollow_spaces: Vec<HollowSpaceProperty>,
    tunnel_furniture: Vec<TunnelFurnitureProperty>,
}

impl AbstractTunnel {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_construction(AbstractConstruction::new(id))
    }

    pub fn from_abstract_construction(abstract_construction: AbstractConstruction) -> Self {
        Self {
            abstract_construction,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            tunnel_installations: Vec::new(),
            tunnel_constructive_elements: Vec::new(),
            hollow_spaces: Vec::new(),
            tunnel_furniture: Vec::new(),
        }
    }
}

pub trait AsAbstractTunnel: AsAbstractConstruction {
    fn abstract_tunnel(&self) -> &AbstractTunnel;

    fn class(&self) -> Option<&TunnelClassValue> {
        self.abstract_tunnel().class.as_ref()
    }

    /// Interprets `class` against a specific code list, if its codeSpace
    /// matches (or `class` has no codeSpace at all).
    fn class_as<T: CodeListValue>(&self) -> Option<T> {
        self.class()?.interpret::<T>()
    }

    fn functions(&self) -> &[TunnelFunctionValue] {
        &self.abstract_tunnel().functions
    }

    /// Interprets `functions` against a specific code list, yielding only
    /// the entries whose codeSpace matches (or have no codeSpace at all).
    fn functions_as<T: CodeListValue + 'static>(&self) -> impl Iterator<Item = T> + '_ {
        self.functions()
            .iter()
            .filter_map(TunnelFunctionValue::interpret::<T>)
    }

    fn usages(&self) -> &[TunnelUsageValue] {
        &self.abstract_tunnel().usages
    }

    /// Interprets `usages` against a specific code list, yielding only
    /// the entries whose codeSpace matches (or have no codeSpace at all).
    fn usages_as<T: CodeListValue + 'static>(&self) -> impl Iterator<Item = T> + '_ {
        self.usages()
            .iter()
            .filter_map(TunnelUsageValue::interpret::<T>)
    }

    fn tunnel_installations(&self) -> &[TunnelInstallationProperty] {
        &self.abstract_tunnel().tunnel_installations
    }

    fn tunnel_constructive_elements(&self) -> &[TunnelConstructiveElementProperty] {
        &self.abstract_tunnel().tunnel_constructive_elements
    }

    fn hollow_spaces(&self) -> &[HollowSpaceProperty] {
        &self.abstract_tunnel().hollow_spaces
    }

    fn tunnel_furniture(&self) -> &[TunnelFurnitureProperty] {
        &self.abstract_tunnel().tunnel_furniture
    }
}

pub trait AsAbstractTunnelMut: AsAbstractConstructionMut + AsAbstractTunnel {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel;

    fn set_class(&mut self, class: TunnelClassValue) {
        self.abstract_tunnel_mut().class = Some(class);
    }

    fn set_class_opt(&mut self, class: Option<TunnelClassValue>) {
        self.abstract_tunnel_mut().class = class;
    }

    fn clear_class(&mut self) {
        self.abstract_tunnel_mut().class = None;
    }

    /// Sets `class`, encoding it with `T`'s code list codeSpace.
    fn set_class_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_tunnel_mut().class = Some(TunnelClassValue::from_value(value));
    }

    fn functions_mut(&mut self) -> &mut [TunnelFunctionValue] {
        &mut self.abstract_tunnel_mut().functions
    }

    fn set_functions(&mut self, functions: Vec<TunnelFunctionValue>) {
        self.abstract_tunnel_mut().functions = functions;
    }

    fn push_function(&mut self, function: TunnelFunctionValue) {
        self.abstract_tunnel_mut().functions.push(function);
    }

    fn extend_functions(&mut self, functions: impl IntoIterator<Item = TunnelFunctionValue>) {
        self.abstract_tunnel_mut().functions.extend(functions);
    }

    /// Appends a function, encoding it with `T`'s code list codeSpace.
    fn push_function_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_tunnel_mut()
            .functions
            .push(TunnelFunctionValue::from_value(value));
    }

    fn usages_mut(&mut self) -> &mut [TunnelUsageValue] {
        &mut self.abstract_tunnel_mut().usages
    }

    fn set_usages(&mut self, usages: Vec<TunnelUsageValue>) {
        self.abstract_tunnel_mut().usages = usages;
    }

    fn push_usage(&mut self, usage: TunnelUsageValue) {
        self.abstract_tunnel_mut().usages.push(usage);
    }

    fn extend_usages(&mut self, usages: impl IntoIterator<Item = TunnelUsageValue>) {
        self.abstract_tunnel_mut().usages.extend(usages);
    }

    /// Appends a usage, encoding it with `T`'s code list codeSpace.
    fn push_usage_as<T: CodeListValue>(&mut self, value: &T) {
        self.abstract_tunnel_mut()
            .usages
            .push(TunnelUsageValue::from_value(value));
    }

    fn tunnel_installations_mut(&mut self) -> &mut [TunnelInstallationProperty] {
        &mut self.abstract_tunnel_mut().tunnel_installations
    }

    fn set_tunnel_installations(&mut self, tunnel_installations: Vec<TunnelInstallationProperty>) {
        self.abstract_tunnel_mut().tunnel_installations = tunnel_installations;
    }

    fn push_tunnel_installation(&mut self, installation: TunnelInstallationProperty) {
        self.abstract_tunnel_mut()
            .tunnel_installations
            .push(installation);
    }

    fn extend_tunnel_installations(
        &mut self,
        installations: impl IntoIterator<Item = TunnelInstallationProperty>,
    ) {
        self.abstract_tunnel_mut()
            .tunnel_installations
            .extend(installations);
    }

    fn tunnel_constructive_elements_mut(&mut self) -> &mut [TunnelConstructiveElementProperty] {
        &mut self.abstract_tunnel_mut().tunnel_constructive_elements
    }

    fn set_tunnel_constructive_elements(
        &mut self,
        tunnel_constructive_elements: Vec<TunnelConstructiveElementProperty>,
    ) {
        self.abstract_tunnel_mut().tunnel_constructive_elements = tunnel_constructive_elements;
    }

    fn push_tunnel_constructive_element(&mut self, element: TunnelConstructiveElementProperty) {
        self.abstract_tunnel_mut()
            .tunnel_constructive_elements
            .push(element);
    }

    fn extend_tunnel_constructive_elements(
        &mut self,
        elements: impl IntoIterator<Item = TunnelConstructiveElementProperty>,
    ) {
        self.abstract_tunnel_mut()
            .tunnel_constructive_elements
            .extend(elements);
    }

    fn hollow_spaces_mut(&mut self) -> &mut [HollowSpaceProperty] {
        &mut self.abstract_tunnel_mut().hollow_spaces
    }

    fn set_hollow_spaces(&mut self, hollow_spaces: Vec<HollowSpaceProperty>) {
        self.abstract_tunnel_mut().hollow_spaces = hollow_spaces;
    }

    fn push_hollow_space(&mut self, hollow_space: HollowSpaceProperty) {
        self.abstract_tunnel_mut().hollow_spaces.push(hollow_space);
    }

    fn extend_hollow_spaces(
        &mut self,
        hollow_spaces: impl IntoIterator<Item = HollowSpaceProperty>,
    ) {
        self.abstract_tunnel_mut()
            .hollow_spaces
            .extend(hollow_spaces);
    }

    fn tunnel_furniture_mut(&mut self) -> &mut [TunnelFurnitureProperty] {
        &mut self.abstract_tunnel_mut().tunnel_furniture
    }

    fn set_tunnel_furniture(&mut self, tunnel_furniture: Vec<TunnelFurnitureProperty>) {
        self.abstract_tunnel_mut().tunnel_furniture = tunnel_furniture;
    }

    fn push_tunnel_furniture(&mut self, tunnel_furniture: TunnelFurnitureProperty) {
        self.abstract_tunnel_mut()
            .tunnel_furniture
            .push(tunnel_furniture);
    }

    fn extend_tunnel_furniture(
        &mut self,
        tunnel_furniture: impl IntoIterator<Item = TunnelFurnitureProperty>,
    ) {
        self.abstract_tunnel_mut()
            .tunnel_furniture
            .extend(tunnel_furniture);
    }
}

impl AsAbstractTunnel for AbstractTunnel {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        self
    }
}

impl AsAbstractTunnelMut for AbstractTunnel {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel {
        self
    }
}

#[macro_export]
macro_rules! impl_abstract_tunnel_traits {
    ($type:ty) => {
        $crate::impl_abstract_construction_traits!($type);

        impl $crate::model::construction::AsAbstractConstruction for $type {
            fn abstract_construction(&self) -> &$crate::model::construction::AbstractConstruction {
                &<$type as $crate::model::tunnel::AsAbstractTunnel>::abstract_tunnel(self)
                    .abstract_construction
            }
        }
    };
}

#[macro_export]
macro_rules! impl_abstract_tunnel_mut_traits {
    ($type:ty) => {
        $crate::impl_abstract_construction_mut_traits!($type);

        impl $crate::model::construction::AsAbstractConstructionMut for $type {
            fn abstract_construction_mut(
                &mut self,
            ) -> &mut $crate::model::construction::AbstractConstruction {
                &mut <$type as $crate::model::tunnel::AsAbstractTunnelMut>::abstract_tunnel_mut(
                    self,
                )
                .abstract_construction
            }
        }
    };
}

impl_abstract_tunnel_traits!(AbstractTunnel);
impl_abstract_tunnel_mut_traits!(AbstractTunnel);

impl IterFeatures for AbstractTunnel {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            self.abstract_construction
                .iter_features()
                .chain(
                    self.tunnel_installations
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.tunnel_constructive_elements
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.hollow_spaces
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                )
                .chain(
                    self.tunnel_furniture
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for AbstractTunnel {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        self.abstract_construction.for_each_feature_mut(f);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for AbstractTunnel {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_construction.compute_envelope()
    }
}

impl ApplyTransform for AbstractTunnel {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_construction.apply_transform(m);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_construction.apply_isometry(isometry);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_construction.apply_translation(vector);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_construction.apply_rotation(rotation);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_construction.apply_scale(scale);

        for prop in &mut self.tunnel_installations {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.tunnel_constructive_elements {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.hollow_spaces {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}
