mod cli;
mod commands;
mod error;

use anyhow::Result;

use crate::cli::{Cli, Commands};
use clap::Parser;
use std::path::Path;
use std::path::PathBuf;

fn main() -> Result<()> {
    tracing_subscriber::fmt::init();
    let cli = Cli::parse();

    match &cli.command {
        Commands::Statistics { file_path } => {
            let file_path = Path::new(file_path).canonicalize()?;
            commands::statistics::run(file_path)?;
        }
        Commands::Validate {
            file_path,
            output_directory_path,
        } => {
            let file_path = Path::new(file_path).canonicalize()?;
            let output_directory_path = PathBuf::from(output_directory_path);

            commands::validate::run(file_path, output_directory_path)?;
        }
    };

    Ok(())
}
