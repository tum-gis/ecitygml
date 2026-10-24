use crate::Error;
use egml::model::xs::AnyUri;

/// The `elevationValue` of an [`Elevation`](super::Elevation), corresponding to `gml:DirectPositionType` with any
/// number of coordinates ([OGC 07-036](https://docs.ogc.org/is/07-036/07-036.pdf), §10.1.4.1).
///
/// Elevations are usually one-dimensional (`srsDimension="1"`), which egml's [`DirectPosition`] cannot hold: it is
/// fixed to three coordinates.
///
/// TODO: replace with an n-dimensional direct position from egml once egml provides one (egml's `DirectPosition`
/// stays 3D, as the geometry types depend on it).
///
/// [`DirectPosition`]: egml::model::geometry::DirectPosition
#[derive(Debug, Clone, PartialEq)]
pub struct ElevationValue {
    coordinates: Vec<f64>,
    srs_dimension: Option<u32>,
    srs_name: Option<AnyUri>,
}

impl ElevationValue {
    /// Creates an elevation value from its coordinates.
    ///
    /// # Errors
    ///
    /// Returns [`Error::EmptyCoordinates`] if `coordinates` is empty, or [`Error::NonFiniteCoordinate`] if a
    /// coordinate is NaN or infinite.
    pub fn new(coordinates: Vec<f64>) -> Result<Self, Error> {
        if coordinates.is_empty() {
            return Err(Error::EmptyCoordinates);
        }
        if let Some(&value) = coordinates.iter().find(|x| !x.is_finite()) {
            return Err(Error::NonFiniteCoordinate { value });
        }
        Ok(Self {
            coordinates,
            srs_dimension: None,
            srs_name: None,
        })
    }

    pub fn coordinates(&self) -> &[f64] {
        &self.coordinates
    }

    pub fn srs_dimension(&self) -> Option<u32> {
        self.srs_dimension
    }

    pub fn set_srs_dimension(&mut self, srs_dimension: Option<u32>) {
        self.srs_dimension = srs_dimension;
    }

    pub fn srs_name(&self) -> Option<&AnyUri> {
        self.srs_name.as_ref()
    }

    pub fn set_srs_name(&mut self, srs_name: Option<AnyUri>) {
        self.srs_name = srs_name;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new_with_one_coordinate() {
        let value = ElevationValue::new(vec![105.3]).expect("should work");
        assert_eq!(value.coordinates(), &[105.3]);
        assert!(value.srs_dimension().is_none());
        assert!(value.srs_name().is_none());
    }

    #[test]
    fn test_new_with_three_coordinates() {
        let value = ElevationValue::new(vec![1.0, 2.0, 3.0]).expect("should work");
        assert_eq!(value.coordinates().len(), 3);
    }

    #[test]
    fn test_new_rejects_empty_coordinates() {
        assert!(matches!(
            ElevationValue::new(Vec::new()),
            Err(Error::EmptyCoordinates)
        ));
    }

    #[test]
    fn test_new_rejects_non_finite_coordinates() {
        assert!(matches!(
            ElevationValue::new(vec![f64::NAN]),
            Err(Error::NonFiniteCoordinate { .. })
        ));
    }

    #[test]
    fn test_srs_attributes_can_be_set() {
        let mut value = ElevationValue::new(vec![105.3]).expect("should work");
        value.set_srs_dimension(Some(1));
        value.set_srs_name(Some(AnyUri::new("urn:ogc:def:crs:EPSG::7837")));
        assert_eq!(value.srs_dimension(), Some(1));
        assert_eq!(
            value.srs_name().map(AnyUri::as_str),
            Some("urn:ogc:def:crs:EPSG::7837")
        );
    }
}
