#[derive(Debug, Clone, PartialEq)]
pub struct Role {
    role: Option<String>,
}

impl Role {
    pub fn new() -> Self {
        Self { role: None }
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
}

impl Default for Role {
    fn default() -> Self {
        Self::new()
    }
}
