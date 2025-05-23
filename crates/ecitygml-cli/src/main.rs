mod cli;
mod commands;

use crate::cli::{Cli, Commands};
use clap::Parser;
use std::path::Path;
use std::path::PathBuf;

fn main() {
    tracing_subscriber::fmt::init();
    let cli = Cli::parse();

    match &cli.command {
        Commands::Statistics { file_path } => {
            let file_path = Path::new(file_path).canonicalize().unwrap();
            commands::statistics::run(file_path);
        }
        Commands::Validate {
            file_path,
            output_directory_path,
        } => {
            let file_path = Path::new(file_path).canonicalize().unwrap();
            let output_directory_path = PathBuf::from(output_directory_path);

            commands::validate::run(file_path, output_directory_path);
        }
    };
}
