use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{
    AbstractOccupiedSpace, AsAbstractOccupiedSpace, AsAbstractOccupiedSpaceMut,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct AbstractFurniture {
    pub(crate) abstract_occupied_space: AbstractOccupiedSpace,
}

impl AbstractFurniture {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_occupied_space(AbstractOccupiedSpace::new(id))
    }

    pub fn from_abstract_occupied_space(abstract_occupied_space: AbstractOccupiedSpace) -> Self {
        Self {
            abstract_occupied_space,
        }
    }
}

pub trait AsAbstractFurniture: AsAbstractOccupiedSpace {
    fn abstract_furniture(&self) -> &AbstractFurniture;
}

pub trait AsAbstractFurnitureMut: AsAbstractOccupiedSpaceMut + AsAbstractFurniture {
    fn abstract_furniture_mut(&mut self) -> &mut AbstractFurniture;
}

impl AsAbstractFurniture for AbstractFurniture {
    fn abstract_furniture(&self) -> &AbstractFurniture {
        self
    }
}

impl AsAbstractFurnitureMut for AbstractFurniture {
    fn abstract_furniture_mut(&mut self) -> &mut AbstractFurniture {
        self
    }
}

#[macro_export]
macro_rules! impl_abstract_furniture_traits {
    ($type:ty) => {
        $crate::impl_abstract_occupied_space_traits!($type);

        impl $crate::model::core::AsAbstractOccupiedSpace for $type {
            fn abstract_occupied_space(&self) -> &$crate::model::core::AbstractOccupiedSpace {
                &<$type as $crate::model::construction::AsAbstractFurniture>::abstract_furniture(
                    self,
                )
                .abstract_occupied_space
            }
        }
    };
}

#[macro_export]
macro_rules! impl_abstract_furniture_mut_traits {
    ($type:ty) => {
        $crate::impl_abstract_occupied_space_mut_traits!($type);

        impl $crate::model::core::AsAbstractOccupiedSpaceMut for $type {
            fn abstract_occupied_space_mut(
                &mut self,
            ) -> &mut $crate::model::core::AbstractOccupiedSpace {
                &mut <$type as $crate::model::construction::AsAbstractFurnitureMut>::abstract_furniture_mut(self).abstract_occupied_space
            }
        }
    };
}

impl_abstract_furniture_traits!(AbstractFurniture);
impl_abstract_furniture_mut_traits!(AbstractFurniture);

impl IterFeatures for AbstractFurniture {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        self.abstract_occupied_space.iter_features()
    }
}

impl ForEachFeatureMut for AbstractFurniture {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        self.abstract_occupied_space.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for AbstractFurniture {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_occupied_space.compute_envelope()
    }
}

impl ApplyTransform for AbstractFurniture {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_occupied_space.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_occupied_space.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_occupied_space.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_occupied_space.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_occupied_space.apply_scale(scale);
    }
}
