use crate::model::building::values::RoomElevationReferenceValue;
use crate::model::construction::enums::HeightStatusValue;
use egml::model::measures::Length;

#[derive(Debug, Clone, PartialEq)]
pub struct RoomHeight {
    high_reference: RoomElevationReferenceValue,
    low_reference: RoomElevationReferenceValue,
    status: HeightStatusValue,
    length: Length,
}

impl RoomHeight {
    pub fn new(
        high_reference: RoomElevationReferenceValue,
        low_reference: RoomElevationReferenceValue,
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

    pub fn high_reference(&self) -> &RoomElevationReferenceValue {
        &self.high_reference
    }

    pub fn set_high_reference(&mut self, high_reference: RoomElevationReferenceValue) {
        self.high_reference = high_reference;
    }

    pub fn low_reference(&self) -> &RoomElevationReferenceValue {
        &self.low_reference
    }

    pub fn set_low_reference(&mut self, low_reference: RoomElevationReferenceValue) {
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

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::basic_types::Code;

    fn room_height() -> RoomHeight {
        RoomHeight::new(
            Code::new("ceiling").into(),
            Code::new("floor").into(),
            HeightStatusValue::Measured,
            Length::new(2.75, "m"),
        )
    }

    #[test]
    fn test_new_sets_all_values() {
        let room_height = room_height();
        assert_eq!(room_height.high_reference().code().value(), "ceiling");
        assert_eq!(room_height.low_reference().code().value(), "floor");
        assert_eq!(room_height.status(), HeightStatusValue::Measured);
        assert_eq!(room_height.length(), &Length::new(2.75, "m"));
    }

    #[test]
    fn test_setters_replace_values() {
        let mut room_height = room_height();
        room_height.set_high_reference(Code::new("roof").into());
        room_height.set_status(HeightStatusValue::Estimated);
        room_height.set_length(Length::new(3.0, "m"));
        assert_eq!(room_height.high_reference().code().value(), "roof");
        assert_eq!(room_height.status(), HeightStatusValue::Estimated);
        assert_eq!(room_height.length(), &Length::new(3.0, "m"));
    }
}
