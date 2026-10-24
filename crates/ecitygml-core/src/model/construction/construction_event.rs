use crate::model::construction::values::EventValue;
use egml::model::xs::Date;

/// An event in the life of a construction, such as its renovation, corresponding to `con:ConstructionEventType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `construction.xsd`).
#[derive(Debug, Clone, PartialEq)]
pub struct ConstructionEvent {
    event: EventValue,
    date_of_event: Date,
    description: Option<String>,
}

impl ConstructionEvent {
    pub fn new(event: EventValue, date_of_event: Date) -> Self {
        Self {
            event,
            date_of_event,
            description: None,
        }
    }

    pub fn event(&self) -> &EventValue {
        &self.event
    }

    pub fn set_event(&mut self, event: EventValue) {
        self.event = event;
    }

    pub fn date_of_event(&self) -> &Date {
        &self.date_of_event
    }

    pub fn set_date_of_event(&mut self, date_of_event: Date) {
        self.date_of_event = date_of_event;
    }

    pub fn description(&self) -> Option<&str> {
        self.description.as_deref()
    }

    pub fn set_description(&mut self, description: String) {
        self.description = Some(description);
    }

    pub fn set_description_opt(&mut self, description: Option<String>) {
        self.description = description;
    }

    pub fn clear_description(&mut self) {
        self.description = None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::basic_types::Code;

    fn renovation() -> ConstructionEvent {
        ConstructionEvent::new(
            Code::new("renovation").into(),
            Date::from_parts(2015, 6, 1, 0).expect("valid date"),
        )
    }

    #[test]
    fn test_new_sets_required_values() {
        let event = renovation();
        assert_eq!(event.event().code().value(), "renovation");
        assert_eq!(
            event.date_of_event(),
            &Date::from_parts(2015, 6, 1, 0).expect("valid date")
        );
        assert!(event.description().is_none());
    }

    #[test]
    fn test_description_can_be_set_and_cleared() {
        let mut event = renovation();
        event.set_description("Facade renovation".to_string());
        assert_eq!(event.description(), Some("Facade renovation"));

        event.clear_description();
        assert!(event.description().is_none());
    }

    #[test]
    fn test_setters_replace_required_values() {
        let mut event = renovation();
        event.set_event(Code::new("demolition").into());
        event.set_date_of_event(Date::from_parts(2030, 1, 1, 0).expect("valid date"));
        assert_eq!(event.event().code().value(), "demolition");
        assert_eq!(
            event.date_of_event(),
            &Date::from_parts(2030, 1, 1, 0).expect("valid date")
        );
    }
}
