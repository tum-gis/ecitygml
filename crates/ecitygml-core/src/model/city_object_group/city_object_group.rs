use crate::model::city_object_group::role::Role;
use crate::model::city_object_group::values::{
    CityObjectGroupClassValue, CityObjectGroupFunctionValue, CityObjectGroupUsageValue,
};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::{AbstractFeatureKindRef, AbstractFeatureKindRefMut};
use crate::model::core::{
    AbstractCityObjectReference, AbstractLogicalSpace, AsAbstractLogicalSpace,
    AsAbstractLogicalSpaceMut,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct CityObjectGroup {
    pub(crate) abstract_logical_space: AbstractLogicalSpace,
    class: Option<CityObjectGroupClassValue>,
    functions: Vec<CityObjectGroupFunctionValue>,
    usages: Vec<CityObjectGroupUsageValue>,
    parent: Option<AbstractCityObjectReference>,
    group_members: Vec<Role>,
}

impl CityObjectGroup {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_logical_space(AbstractLogicalSpace::new(id))
    }

    pub fn from_abstract_logical_space(abstract_logical_space: AbstractLogicalSpace) -> Self {
        Self {
            abstract_logical_space,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
            parent: None,
            group_members: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&CityObjectGroupClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: CityObjectGroupClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<CityObjectGroupClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[CityObjectGroupFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [CityObjectGroupFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<CityObjectGroupFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: CityObjectGroupFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = CityObjectGroupFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[CityObjectGroupUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [CityObjectGroupUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<CityObjectGroupUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: CityObjectGroupUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(&mut self, usages: impl IntoIterator<Item = CityObjectGroupUsageValue>) {
        self.usages.extend(usages);
    }

    pub fn parent(&self) -> Option<&AbstractCityObjectReference> {
        self.parent.as_ref()
    }

    pub fn set_parent(&mut self, parent: AbstractCityObjectReference) {
        self.parent = Some(parent);
    }

    pub fn set_parent_opt(&mut self, parent: Option<AbstractCityObjectReference>) {
        self.parent = parent;
    }

    pub fn clear_parent(&mut self) {
        self.parent = None;
    }

    pub fn group_members(&self) -> &[Role] {
        &self.group_members
    }

    pub fn group_members_mut(&mut self) -> &mut [Role] {
        &mut self.group_members
    }

    pub fn set_group_members(&mut self, group_members: Vec<Role>) {
        self.group_members = group_members;
    }

    pub fn push_group_member(&mut self, group_member: Role) {
        self.group_members.push(group_member);
    }

    pub fn extend_group_members(&mut self, group_members: impl IntoIterator<Item = Role>) {
        self.group_members.extend(group_members);
    }
}

impl AsAbstractLogicalSpace for CityObjectGroup {
    fn abstract_logical_space(&self) -> &AbstractLogicalSpace {
        &self.abstract_logical_space
    }
}

impl AsAbstractLogicalSpaceMut for CityObjectGroup {
    fn abstract_logical_space_mut(&mut self) -> &mut AbstractLogicalSpace {
        &mut self.abstract_logical_space
    }
}

crate::impl_abstract_logical_space_traits!(CityObjectGroup);
crate::impl_abstract_logical_space_mut_traits!(CityObjectGroup);
crate::impl_has_feature_type!(CityObjectGroup, CityObjectGroup);

impl IterFeatures for CityObjectGroup {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_logical_space.iter_features()))
    }
}

impl ForEachFeatureMut for CityObjectGroup {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_logical_space.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for CityObjectGroup {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_logical_space.compute_envelope()
    }
}

impl ApplyTransform for CityObjectGroup {
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
