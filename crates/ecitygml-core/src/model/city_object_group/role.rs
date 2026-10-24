use crate::model::core::AbstractCityObjectReference;

#[derive(Debug, Clone, PartialEq)]
pub struct Role {
    role: Option<String>,
    group_member: AbstractCityObjectReference,
}

impl Role {
    pub fn new(group_member: AbstractCityObjectReference) -> Self {
        Self {
            role: None,
            group_member,
        }
    }

    pub fn role(&self) -> Option<&str> {
        self.role.as_deref()
    }

    pub fn set_role(&mut self, role: String) {
        self.role = Some(role);
    }

    pub fn set_role_opt(&mut self, role: Option<String>) {
        self.role = role;
    }

    pub fn clear_role(&mut self) {
        self.role = None;
    }

    pub fn group_member(&self) -> &AbstractCityObjectReference {
        &self.group_member
    }

    pub fn set_group_member(&mut self, group_member: AbstractCityObjectReference) {
        self.group_member = group_member;
    }
}
