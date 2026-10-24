use crate::impl_abstract_unoccupied_space_mut_traits;
use crate::impl_abstract_unoccupied_space_traits;
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{
    AbstractUnoccupiedSpace, AsAbstractUnoccupiedSpace, AsAbstractUnoccupiedSpaceMut,
};
use crate::model::tunnel::TunnelFurnitureProperty;
use crate::model::tunnel::values::{
    HollowSpaceClassValue, HollowSpaceFunctionValue, HollowSpaceUsageValue,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct HollowSpace {
    pub(crate) abstract_unoccupied_space: AbstractUnoccupiedSpace,
    class: Option<HollowSpaceClassValue>,
    functions: Vec<HollowSpaceFunctionValue>,
    usages: Vec<HollowSpaceUsageValue>,
    tunnel_furniture: Vec<TunnelFurnitureProperty>,
}

impl HollowSpace {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_unoccupied_space(AbstractUnoccupiedSpace::new(id))
    }

    pub fn from_abstract_unoccupied_space(
        abstract_unoccupied_space: AbstractUnoccupiedSpace,
    ) -> Self {
        HollowSpace {
            abstract_unoccupied_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            tunnel_furniture: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&HollowSpaceClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: HollowSpaceClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<HollowSpaceClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[HollowSpaceFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [HollowSpaceFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<HollowSpaceFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: HollowSpaceFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = HollowSpaceFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[HollowSpaceUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [HollowSpaceUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<HollowSpaceUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: HollowSpaceUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = HollowSpaceUsageValue>) {
        self.usages.extend(usages);
    }

    pub fn tunnel_furniture(&self) -> &[TunnelFurnitureProperty] {
        &self.tunnel_furniture
    }

    pub fn tunnel_furniture_mut(&mut self) -> &mut [TunnelFurnitureProperty] {
        &mut self.tunnel_furniture
    }

    pub fn set_tunnel_furniture(&mut self, tunnel_furniture: Vec<TunnelFurnitureProperty>) {
        self.tunnel_furniture = tunnel_furniture;
    }

    pub fn push_tunnel_furniture(&mut self, tunnel_furniture: TunnelFurnitureProperty) {
        self.tunnel_furniture.push(tunnel_furniture);
    }

    pub fn extend_tunnel_furniture(
        &mut self,
        tunnel_furniture: impl IntoIterator<Item = TunnelFurnitureProperty>,
    ) {
        self.tunnel_furniture.extend(tunnel_furniture);
    }
}

impl AsAbstractUnoccupiedSpace for HollowSpace {
    fn abstract_unoccupied_space(&self) -> &AbstractUnoccupiedSpace {
        &self.abstract_unoccupied_space
    }
}

impl AsAbstractUnoccupiedSpaceMut for HollowSpace {
    fn abstract_unoccupied_space_mut(&mut self) -> &mut AbstractUnoccupiedSpace {
        &mut self.abstract_unoccupied_space
    }
}

impl_abstract_unoccupied_space_traits!(HollowSpace);
impl_abstract_unoccupied_space_mut_traits!(HollowSpace);
crate::impl_has_feature_type!(HollowSpace, HollowSpace);

impl IterFeatures for HollowSpace {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into())
                .chain(self.abstract_unoccupied_space.iter_features())
                .chain(
                    self.tunnel_furniture
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for HollowSpace {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_unoccupied_space.for_each_feature_mut(f);

        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for HollowSpace {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_unoccupied_space.compute_envelope()
    }
}

impl ApplyTransform for HollowSpace {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_unoccupied_space.apply_transform(m);

        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_unoccupied_space.apply_isometry(isometry);

        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_unoccupied_space.apply_translation(vector);

        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_unoccupied_space.apply_rotation(rotation);

        for prop in &mut self.tunnel_furniture {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_unoccupied_space.apply_scale(scale);

        for prop in &mut self.tunnel_furniture {
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

    fn hollow_space() -> HollowSpace {
        HollowSpace::new(Id::try_from("hollow_space").expect("valid id"))
    }

    #[test]
    fn test_feature_type() {
        assert_eq!(hollow_space().feature_type(), FeatureType::HollowSpace);
    }

    #[test]
    fn test_iter_features_yields_itself() {
        let feature_types: Vec<FeatureType> = hollow_space()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, vec![FeatureType::HollowSpace]);
    }

    #[test]
    fn test_for_each_feature_mut_visits_itself() {
        let mut feature_types = Vec::new();
        hollow_space().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, vec![FeatureType::HollowSpace]);
    }

    #[test]
    fn test_converts_to_and_from_abstract_unoccupied_space_kind() {
        let kind: AbstractUnoccupiedSpaceKind = hollow_space().into();
        assert_eq!(kind.feature_type(), FeatureType::HollowSpace);

        let round_tripped = HollowSpace::try_from(kind).expect("should convert back");
        assert_eq!(round_tripped, hollow_space());
    }
}
