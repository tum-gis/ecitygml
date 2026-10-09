use slotmap::{DefaultKey, Key};
use std::num::{NonZeroU64, TryFromIntError};

/// A slotmap key in its FFI form.
///
/// The key's version is a `NonZeroU32` stored in the upper 32 bits, so the FFI value is
/// never zero; storing it as [`NonZeroU64`] makes `Option<InternalKey>` as small as the key.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct InternalKey(NonZeroU64);

impl TryFrom<u64> for InternalKey {
    type Error = TryFromIntError;

    fn try_from(key: u64) -> Result<Self, Self::Error> {
        NonZeroU64::try_from(key).map(Self)
    }
}

impl From<InternalKey> for DefaultKey {
    fn from(key: InternalKey) -> Self {
        let key_data = slotmap::KeyData::from_ffi(key.0.get());
        key_data.into()
    }
}

impl From<DefaultKey> for InternalKey {
    fn from(key: DefaultKey) -> Self {
        let key_data = key.data().as_ffi();
        InternalKey(NonZeroU64::new(key_data).expect("slotmap key versions are non-zero"))
    }
}

#[cfg(test)]
mod tests {
    use super::InternalKey;
    use slotmap::{DefaultKey, Key, SlotMap};
    use std::mem::size_of;

    #[test]
    fn option_has_no_overhead() {
        assert_eq!(size_of::<Option<InternalKey>>(), size_of::<InternalKey>());
    }

    #[test]
    fn round_trips_through_default_key() {
        let mut slot_map = SlotMap::new();
        let key = slot_map.insert(());
        assert_eq!(DefaultKey::from(InternalKey::from(key)), key);
    }

    #[test]
    fn round_trips_null_key() {
        let key = DefaultKey::null();
        assert_eq!(DefaultKey::from(InternalKey::from(key)), key);
    }

    #[test]
    fn rejects_zero() {
        assert!(InternalKey::try_from(0).is_err());
        assert!(InternalKey::try_from(1).is_ok());
    }
}
