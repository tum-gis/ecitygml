use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::construction::{
    AbstractInstallation, AsAbstractInstallation, AsAbstractInstallationMut,
};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::values::{
    TunnelInstallationClassValue, TunnelInstallationFunctionValue, TunnelInstallationUsageValue,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct TunnelInstallation {
    pub(crate) abstract_installation: AbstractInstallation,
    class: Option<TunnelInstallationClassValue>,
    functions: Vec<TunnelInstallationFunctionValue>,
    usages: Vec<TunnelInstallationUsageValue>,
}

impl TunnelInstallation {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_installation(AbstractInstallation::new(id))
    }

    pub fn from_abstract_installation(abstract_installation: AbstractInstallation) -> Self {
        Self {
            abstract_installation,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&TunnelInstallationClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: TunnelInstallationClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<TunnelInstallationClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[TunnelInstallationFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [TunnelInstallationFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<TunnelInstallationFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: TunnelInstallationFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = TunnelInstallationFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[TunnelInstallationUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [TunnelInstallationUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<TunnelInstallationUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: TunnelInstallationUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(
        &mut self,
        usages: impl IntoIterator<Item = TunnelInstallationUsageValue>,
    ) {
        self.usages.extend(usages);
    }
}

impl AsAbstractInstallation for TunnelInstallation {
    fn abstract_installation(&self) -> &AbstractInstallation {
        &self.abstract_installation
    }
}

impl AsAbstractInstallationMut for TunnelInstallation {
    fn abstract_installation_mut(&mut self) -> &mut AbstractInstallation {
        &mut self.abstract_installation
    }
}

crate::impl_abstract_installation_traits!(TunnelInstallation);
crate::impl_abstract_installation_mut_traits!(TunnelInstallation);
crate::impl_has_feature_type!(TunnelInstallation, TunnelInstallation);

impl IterFeatures for TunnelInstallation {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_installation.iter_features()))
    }
}

impl ForEachFeatureMut for TunnelInstallation {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_installation.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for TunnelInstallation {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_installation.compute_envelope()
    }
}

impl ApplyTransform for TunnelInstallation {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_installation.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_installation.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_installation.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_installation.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_installation.apply_scale(scale);
    }
}
