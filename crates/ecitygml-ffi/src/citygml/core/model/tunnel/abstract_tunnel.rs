//! Methods of ecitygml's `AbstractTunnel`, generated into the bridge of every tunnel type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: tunnel_installations, tunnel_constructive_elements, hollow_spaces,
//! tunnel_furniture.

#[diplomat::macro_rules]
macro_rules! impl_abstract_tunnel_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(
            &'a self,
        ) -> Option<&'a crate::citygml::core::model::tunnel::values::tunnel_class_value::ffi::TunnelClassValue> {
            ecitygml::model::tunnel::AsAbstractTunnel::class(&self.0)
                .map(crate::citygml::core::model::tunnel::values::tunnel_class_value::ffi::TunnelClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::tunnel::values::tunnel_function_value::ffi::TunnelFunctionValueIterator<'a>> {
            Box::new(crate::citygml::core::model::tunnel::values::tunnel_function_value::ffi::TunnelFunctionValueIterator(
                ecitygml::model::tunnel::AsAbstractTunnel::functions(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::tunnel::values::tunnel_usage_value::ffi::TunnelUsageValueIterator<'a>> {
            Box::new(crate::citygml::core::model::tunnel::values::tunnel_usage_value::ffi::TunnelUsageValueIterator(
                ecitygml::model::tunnel::AsAbstractTunnel::usages(&self.0).iter(),
            ))
        }
    };
}
