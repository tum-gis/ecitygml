use strum_macros::Display;

#[derive(Debug, Copy, Hash, Eq, Clone, PartialEq, Display)]
pub enum HeightStatusValue {
    Estimated,
    Measured,
}
