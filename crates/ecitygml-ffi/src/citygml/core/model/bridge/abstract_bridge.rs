//! Methods of ecitygml's `AbstractBridge`, generated into the bridge of every bridge type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: bridge_installations, bridge_constructive_elements, bridge_rooms, bridge_furniture.

#[diplomat::macro_rules]
macro_rules! impl_abstract_bridge_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(
            &'a self,
        ) -> Option<&'a crate::citygml::core::model::bridge::values::bridge_class_value::ffi::BridgeClassValue> {
            ecitygml::model::bridge::AsAbstractBridge::class(&self.0)
                .map(crate::citygml::core::model::bridge::values::bridge_class_value::ffi::BridgeClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::bridge::values::bridge_function_value::ffi::BridgeFunctionValueIterator<'a>> {
            Box::new(crate::citygml::core::model::bridge::values::bridge_function_value::ffi::BridgeFunctionValueIterator(
                ecitygml::model::bridge::AsAbstractBridge::functions(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::bridge::values::bridge_usage_value::ffi::BridgeUsageValueIterator<'a>> {
            Box::new(crate::citygml::core::model::bridge::values::bridge_usage_value::ffi::BridgeUsageValueIterator(
                ecitygml::model::bridge::AsAbstractBridge::usages(&self.0).iter(),
            ))
        }

        /// Not in Kotlin: diplomat-tool 0.16's Kotlin backend generates invalid code for an
        /// `Option<bool>` return (`returnVal.option()? > 0`).
        #[diplomat::attr(kotlin, disable)]
        pub fn is_movable(&self) -> Option<bool> {
            ecitygml::model::bridge::AsAbstractBridge::is_movable(&self.0)
        }
    };
}
