use crate::model::common::arena::{ArenaProperties, HasArenaProperties, HasArenaPropertiesMut};
use egml::model::base::{
    AssociationAttributes, HasAssociationAttributes, HasAssociationAttributesMut,
    HasOwnershipAttributes, HasOwnershipAttributesMut, OwnershipAttributes, Property,
};
use egml::model::xlink::HRef;

/// A [`Property`] whose object can be moved into a `CityModel` arena, leaving
/// behind the [`InternalKey`](crate::model::common::arena::InternalKey) it is stored under.
#[derive(Debug, Clone, PartialEq)]
pub struct ArenaProperty<T> {
    property: Property<T>,
    arena: ArenaProperties,
}

impl<T> ArenaProperty<T> {
    pub fn new(
        object: Option<T>,
        association: AssociationAttributes,
        ownership: OwnershipAttributes,
    ) -> Self {
        Self::from_property(Property::new(object, association, ownership))
    }

    pub fn from_object(object: T) -> Self {
        Self::from_property(Property::from_object(object))
    }

    pub fn from_href(href: HRef) -> Self {
        Self::from_property(Property::from_href(href))
    }

    pub fn from_property(property: Property<T>) -> Self {
        Self {
            property,
            arena: ArenaProperties::default(),
        }
    }

    pub fn object(&self) -> Option<&T> {
        self.property.object()
    }

    pub fn object_mut(&mut self) -> Option<&mut T> {
        self.property.object_mut()
    }

    pub fn take_object(&mut self) -> Option<T> {
        self.property.take_object()
    }

    pub fn set_object(&mut self, object: T) {
        self.property.set_object(object);
    }

    pub fn set_object_opt(&mut self, object: Option<T>) {
        self.property.set_object_opt(object);
    }

    pub fn clear_object(&mut self) {
        self.property.clear_object();
    }
}

impl<T> Default for ArenaProperty<T> {
    fn default() -> Self {
        Self::from_property(Property::default())
    }
}

impl<T> HasAssociationAttributes for ArenaProperty<T> {
    fn association(&self) -> &AssociationAttributes {
        self.property.association()
    }
}

impl<T> HasAssociationAttributesMut for ArenaProperty<T> {
    fn association_mut(&mut self) -> &mut AssociationAttributes {
        self.property.association_mut()
    }
}

impl<T> HasOwnershipAttributes for ArenaProperty<T> {
    fn ownership(&self) -> &OwnershipAttributes {
        self.property.ownership()
    }
}

impl<T> HasOwnershipAttributesMut for ArenaProperty<T> {
    fn ownership_mut(&mut self) -> &mut OwnershipAttributes {
        self.property.ownership_mut()
    }
}

impl<T> HasArenaProperties for ArenaProperty<T> {
    fn arena_properties(&self) -> &ArenaProperties {
        &self.arena
    }
}

impl<T> HasArenaPropertiesMut for ArenaProperty<T> {
    fn arena_properties_mut(&mut self) -> &mut ArenaProperties {
        &mut self.arena
    }
}
