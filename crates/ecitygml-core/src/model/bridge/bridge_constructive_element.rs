use crate::model::bridge::values::{
    BridgeConstructiveElementClassValue, BridgeConstructiveElementFunctionValue,
    BridgeConstructiveElementUsageValue,
};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::construction::{
    AbstractConstructiveElement, AsAbstractConstructiveElement, AsAbstractConstructiveElementMut,
};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct BridgeConstructiveElement {
    pub(crate) abstract_constructive_element: AbstractConstructiveElement,
    class: Option<BridgeConstructiveElementClassValue>,
    functions: Vec<BridgeConstructiveElementFunctionValue>,
    usages: Vec<BridgeConstructiveElementUsageValue>,
}

impl BridgeConstructiveElement {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_constructive_element(AbstractConstructiveElement::new(id))
    }

    pub fn from_abstract_constructive_element(
        abstract_constructive_element: AbstractConstructiveElement,
    ) -> Self {
        Self {
            abstract_constructive_element,
            class: None,
            functions: Vec::new(),
            usages: Vec::new(),
        }
    }

    pub fn class(&self) -> Option<&BridgeConstructiveElementClassValue> {
        self.class.as_ref()
    }

    pub fn set_class(&mut self, class: BridgeConstructiveElementClassValue) {
        self.class = Some(class);
    }

    pub fn set_class_opt(&mut self, class: Option<BridgeConstructiveElementClassValue>) {
        self.class = class;
    }

    pub fn clear_class(&mut self) {
        self.class = None;
    }

    pub fn functions(&self) -> &[BridgeConstructiveElementFunctionValue] {
        &self.functions
    }

    pub fn functions_mut(&mut self) -> &mut [BridgeConstructiveElementFunctionValue] {
        &mut self.functions
    }

    pub fn set_functions(&mut self, functions: Vec<BridgeConstructiveElementFunctionValue>) {
        self.functions = functions;
    }

    pub fn push_function(&mut self, function: BridgeConstructiveElementFunctionValue) {
        self.functions.push(function);
    }

    pub fn extend_functions(
        &mut self,
        functions: impl IntoIterator<Item = BridgeConstructiveElementFunctionValue>,
    ) {
        self.functions.extend(functions);
    }

    pub fn usages(&self) -> &[BridgeConstructiveElementUsageValue] {
        &self.usages
    }

    pub fn usages_mut(&mut self) -> &mut [BridgeConstructiveElementUsageValue] {
        &mut self.usages
    }

    pub fn set_usages(&mut self, usages: Vec<BridgeConstructiveElementUsageValue>) {
        self.usages = usages;
    }

    pub fn push_usage(&mut self, usage: BridgeConstructiveElementUsageValue) {
        self.usages.push(usage);
    }

    pub fn extend_usages(
        &mut self,
        usages: impl IntoIterator<Item = BridgeConstructiveElementUsageValue>,
    ) {
        self.usages.extend(usages);
    }
}

impl AsAbstractConstructiveElement for BridgeConstructiveElement {
    fn abstract_constructive_element(&self) -> &AbstractConstructiveElement {
        &self.abstract_constructive_element
    }
}

impl AsAbstractConstructiveElementMut for BridgeConstructiveElement {
    fn abstract_constructive_element_mut(&mut self) -> &mut AbstractConstructiveElement {
        &mut self.abstract_constructive_element
    }
}

crate::impl_abstract_constructive_element_traits!(BridgeConstructiveElement);
crate::impl_abstract_constructive_element_mut_traits!(BridgeConstructiveElement);
crate::impl_has_feature_type!(BridgeConstructiveElement, BridgeConstructiveElement);

impl IterFeatures for BridgeConstructiveElement {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into()).chain(self.abstract_constructive_element.iter_features()),
        )
    }
}

impl ForEachFeatureMut for BridgeConstructiveElement {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_constructive_element.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for BridgeConstructiveElement {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_constructive_element.compute_envelope()
    }
}

impl ApplyTransform for BridgeConstructiveElement {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_constructive_element.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_constructive_element.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_constructive_element.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_constructive_element.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_constructive_element.apply_scale(scale);
    }
}
