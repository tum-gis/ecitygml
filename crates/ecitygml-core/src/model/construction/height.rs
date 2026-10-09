use crate::model::construction::enums::HeightStatusValue;
use crate::model::construction::values::ElevationReferenceValue;
use egml::model::measures::Length;

#[derive(Debug, Clone, PartialEq)]
pub struct Height {
    high_reference: ElevationReferenceValue,
    low_reference: ElevationReferenceValue,
    status: HeightStatusValue,
    length: Length,
}

impl Height {
    pub fn new(
        high_reference: ElevationReferenceValue,
        low_reference: ElevationReferenceValue,
        status: HeightStatusValue,
        length: Length,
    ) -> Self {
        Self {
            high_reference,
            low_reference,
            status,
            length,
        }
    }

    pub fn high_reference(&self) -> &ElevationReferenceValue {
        &self.high_reference
    }

    pub fn set_high_reference(&mut self, high_reference: ElevationReferenceValue) {
        self.high_reference = high_reference;
    }

    pub fn low_reference(&self) -> &ElevationReferenceValue {
        &self.low_reference
    }

    pub fn set_low_reference(&mut self, low_reference: ElevationReferenceValue) {
        self.low_reference = low_reference;
    }

    pub fn status(&self) -> HeightStatusValue {
        self.status
    }

    pub fn set_status(&mut self, status: HeightStatusValue) {
        self.status = status;
    }

    pub fn length(&self) -> &Length {
        &self.length
    }

    pub fn set_length(&mut self, length: Length) {
        self.length = length;
    }
}
