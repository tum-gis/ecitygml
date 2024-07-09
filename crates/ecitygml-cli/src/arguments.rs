use clap::{Parser, Subcommand};

#[derive(Parser)]
#[clap(author, version, about, long_about = None, propagate_version = true)]
pub struct Arguments {
    #[clap(subcommand)]
    pub command: Commands,
}

#[derive(Subcommand)]
pub enum Commands {
    /// Compute some statistics about the dataset
    Statistics {
        /// Input directory
        #[clap(short, long)]
        file_path: String,
    },

    /// Validate the dataset
    Validate {
        /// Input directory
        #[clap(short, long)]
        file_path: String,
        /// Output directory
        #[clap(short, long)]
        output_directory_path: String,
    },
}
