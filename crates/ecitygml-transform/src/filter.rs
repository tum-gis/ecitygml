use crate::error::Error;
use ecitygml_core::model::city_model::CitygmlModel;
use ecitygml_core::model::core::{OccupiedSpace, Space, ThematicSurface};
use egml::model::geometry::Envelope;
use egml::operations::geometry::Geometry;

pub fn filter_by_bounding_box(
    mut city_model: CitygmlModel,
    filter_envelope: &Envelope,
) -> Result<CitygmlModel, Error> {
    city_model.building.retain(|f| {
        f.wall_surface
            .iter()
            .any(|w| contains_thematic_surface(filter_envelope, &w.thematic_surface))
            || f.roof_surface
                .iter()
                .any(|w| contains_thematic_surface(filter_envelope, &w.thematic_surface))
            || f.ground_surface
                .iter()
                .any(|w| contains_thematic_surface(filter_envelope, &w.thematic_surface))
            || f.building_constructive_element
                .iter()
                .any(|w| contains_occupied_space(filter_envelope, &w.occupied_space))
    });

    // TODO road

    city_model
        .city_furniture
        .retain(|f| contains_occupied_space(filter_envelope, &f.occupied_space));

    city_model
        .solitary_vegetation_object
        .retain(|f| contains_occupied_space(filter_envelope, &f.occupied_space));

    Ok(city_model)
}

fn contains_thematic_surface(
    filter_envelope: &Envelope,
    thematic_surface: &ThematicSurface,
) -> bool {
    if let Some(g) = &thematic_surface.lod0_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &thematic_surface.lod1_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &thematic_surface.lod2_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &thematic_surface.lod3_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }

    false
}

fn contains_occupied_space(filter_envelope: &Envelope, occupied_space: &OccupiedSpace) -> bool {
    if let Some(g) = &occupied_space.lod1_implicit_representation
        && filter_envelope.contains(&g.reference_point)
    {
        return true;
    }
    if let Some(g) = &occupied_space.lod2_implicit_representation
        && filter_envelope.contains(&g.reference_point)
    {
        return true;
    }
    if let Some(g) = &occupied_space.lod3_implicit_representation
        && filter_envelope.contains(&g.reference_point)
    {
        return true;
    }

    contains_space(filter_envelope, &occupied_space.space)
}

fn contains_space(filter_envelope: &Envelope, space: &Space) -> bool {
    if let Some(g) = &space.lod1_solid
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &space.lod2_solid
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &space.lod3_solid
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }

    if let Some(g) = &space.lod0_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &space.lod2_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }
    if let Some(g) = &space.lod3_multi_surface
        && filter_envelope.contains_envelope_partially(&g.envelope())
    {
        return true;
    }

    false
}
