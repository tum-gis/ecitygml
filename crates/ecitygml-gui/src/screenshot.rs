use crate::app::ScreenshotStatus;
use crate::platform;
use crate::scene::Scene;
use chrono::Local;
use ecitygml_core::model::common::FeatureType;
use image::{ImageFormat, RgbaImage};
use std::collections::HashSet;
use std::io::Cursor;
use three_d::{
    Camera, ClearState, Context, DepthTexture2D, Interpolation, RenderTarget, Texture2D, Wrapping,
};

/// Clear color used only for screenshot exports — white, and rendered into an
/// off-screen target so it never affects (or flashes on) the interactive viewport,
/// which keeps its own background (see `scene::VIEWPORT_BACKGROUND`).
const BACKGROUND: ClearState = ClearState::color_and_depth(1.0, 1.0, 1.0, 1.0, 1.0);

/// Renders `scene` into an off-screen target sized `width` x `height` with a white
/// background, then prompts for a save location and writes it out as a PNG.
///
/// Returns `None` if the user cancelled the save dialog (in which case the caller
/// should leave any previous status untouched).
pub fn capture_and_save(
    context: &Context,
    scene: &Scene,
    camera: &Camera,
    hidden: &HashSet<FeatureType>,
    width: u32,
    height: u32,
) -> Option<ScreenshotStatus> {
    let color = Texture2D::new_empty::<[u8; 4]>(
        context,
        width,
        height,
        Interpolation::Nearest,
        Interpolation::Nearest,
        None,
        Wrapping::ClampToEdge,
        Wrapping::ClampToEdge,
    );
    let depth = DepthTexture2D::new::<f32>(
        context,
        width,
        height,
        Wrapping::ClampToEdge,
        Wrapping::ClampToEdge,
    );
    let target = RenderTarget::new(color.as_color_target(None), depth.as_depth_target());

    scene.render(&target, camera, hidden, BACKGROUND);
    let pixels: Vec<[u8; 4]> = target.read_color();

    save(pixels, width, height)
}

fn save(pixels: Vec<[u8; 4]>, width: u32, height: u32) -> Option<ScreenshotStatus> {
    let data: Vec<u8> = pixels.into_iter().flatten().collect();
    let Some(image) = RgbaImage::from_raw(width, height, data) else {
        return Some(ScreenshotStatus::Error(
            "captured pixel buffer did not match the viewport size".to_string(),
        ));
    };

    let default_name = format!(
        "citygml-screenshot-{}.png",
        Local::now().format("%Y-%m-%d_%H%M%S")
    );
    let mut png = Vec::new();
    if let Err(e) = image.write_to(&mut Cursor::new(&mut png), ImageFormat::Png) {
        return Some(ScreenshotStatus::Error(e.to_string()));
    }

    Some(
        match platform::save_file(&png, &default_name, ("PNG image", &["png"]))? {
            Ok(location) => ScreenshotStatus::Saved(location),
            Err(e) => ScreenshotStatus::Error(e),
        },
    )
}
