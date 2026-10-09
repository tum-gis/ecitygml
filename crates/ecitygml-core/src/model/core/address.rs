use egml::model::geometry::aggregates::MultiPointProperty;
use egml::model::xal;

#[derive(Debug, Clone, PartialEq)]
pub struct Address {
    xal_address: xal::Address,
    multi_point: Option<Box<MultiPointProperty>>,
}

impl Address {
    pub fn new(xal_address: xal::Address) -> Self {
        Self {
            xal_address,
            multi_point: None,
        }
    }

    pub fn xal_address(&self) -> &xal::Address {
        &self.xal_address
    }

    pub fn set_xal_address(&mut self, xal_address: xal::Address) {
        self.xal_address = xal_address;
    }

    pub fn multi_point(&self) -> Option<&MultiPointProperty> {
        self.multi_point.as_deref()
    }

    pub fn set_multi_point(&mut self, multi_point: Option<MultiPointProperty>) {
        self.multi_point = multi_point.map(Box::new);
    }
}
