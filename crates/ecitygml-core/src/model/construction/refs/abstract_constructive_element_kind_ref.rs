use crate::impl_try_from_occupied_space_kind_ref_for_enum;
use crate::model::bridge::BridgeConstructiveElement;
use crate::model::building::BuildingConstructiveElement;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::construction::{
    AbstractConstructiveElement, AbstractConstructiveElementKind, AsAbstractConstructiveElement,
};
use crate::model::tunnel::TunnelConstructiveElement;
use egml::model::common::ComputeEnvelope;
use egml::model::geometry::Envelope;

#[derive(Debug, Clone, Copy)]
pub enum AbstractConstructiveElementKindRef<'a> {
    BuildingConstructiveElement(&'a BuildingConstructiveElement),
    BridgeConstructiveElement(&'a BridgeConstructiveElement),
    TunnelConstructiveElement(&'a TunnelConstructiveElement),
}

impl<'a> From<&'a AbstractConstructiveElementKind> for AbstractConstructiveElementKindRef<'a> {
    fn from(item: &'a AbstractConstructiveElementKind) -> Self {
        match item {
            AbstractConstructiveElementKind::BuildingConstructiveElement(x) => {
                Self::BuildingConstructiveElement(x)
            }
            AbstractConstructiveElementKind::BridgeConstructiveElement(x) => {
                Self::BridgeConstructiveElement(x)
            }
            AbstractConstructiveElementKind::TunnelConstructiveElement(x) => {
                Self::TunnelConstructiveElement(x)
            }
        }
    }
}

impl<'a> AsAbstractConstructiveElement for AbstractConstructiveElementKindRef<'a> {
    fn abstract_constructive_element(&self) -> &AbstractConstructiveElement {
        match self {
            Self::BuildingConstructiveElement(x) => x.abstract_constructive_element(),
            Self::BridgeConstructiveElement(x) => x.abstract_constructive_element(),
            Self::TunnelConstructiveElement(x) => x.abstract_constructive_element(),
        }
    }
}
crate::impl_abstract_constructive_element_traits!(AbstractConstructiveElementKindRef<'_>);

impl<'a> HasFeatureType for AbstractConstructiveElementKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::BuildingConstructiveElement(_) => FeatureType::BuildingConstructiveElement,
            Self::BridgeConstructiveElement(_) => FeatureType::BridgeConstructiveElement,
            Self::TunnelConstructiveElement(_) => FeatureType::TunnelConstructiveElement,
        }
    }
}

#[macro_export]
macro_rules! impl_from_constructive_element_kind_ref {
    ($type:ident) => {
        impl<'a> From<&'a $type>
            for $crate::model::construction::refs::AbstractConstructiveElementKindRef<'a>
        {
            fn from(x: &'a $type) -> Self {
                $crate::model::construction::refs::AbstractConstructiveElementKindRef::$type(
                    x.into(),
                )
            }
        }
        $crate::impl_from_for_occupied_space_kind_ref!(AbstractConstructiveElementKind, $type);
    };
}
impl_from_constructive_element_kind_ref!(BuildingConstructiveElement);
impl_from_constructive_element_kind_ref!(BridgeConstructiveElement);
impl_from_constructive_element_kind_ref!(TunnelConstructiveElement);

#[macro_export]
macro_rules! impl_try_from_constructive_element_kind_ref {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractConstructiveElementKindRef<'a>>
            for &'a $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractConstructiveElementKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractConstructiveElementKindRef::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind_ref!(AbstractConstructiveElementKind, $type);
    };
}
impl_try_from_constructive_element_kind_ref!(BuildingConstructiveElement);
impl_try_from_constructive_element_kind_ref!(BridgeConstructiveElement);
impl_try_from_constructive_element_kind_ref!(TunnelConstructiveElement);
impl_try_from_occupied_space_kind_ref_for_enum!(
    AbstractConstructiveElementKind,
    AbstractConstructiveElementKindRef
);

impl<'a> ComputeEnvelope for AbstractConstructiveElementKindRef<'a> {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractConstructiveElementKindRef::BuildingConstructiveElement(x) => {
                x.compute_envelope()
            }
            AbstractConstructiveElementKindRef::BridgeConstructiveElement(x) => {
                x.compute_envelope()
            }
            AbstractConstructiveElementKindRef::TunnelConstructiveElement(x) => {
                x.compute_envelope()
            }
        }
    }
}
