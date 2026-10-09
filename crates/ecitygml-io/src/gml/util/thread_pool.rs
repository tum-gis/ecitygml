use std::sync::OnceLock;

// Dedicated thread pool with a larger stack to accommodate deeply nested rayon
// parallelism (collect_children → deserialize → collect_children → …).
//
// Where no threads can be spawned (e.g. WebAssembly), it falls back to the calling thread as the only
// worker, like rayon's global pool does; that thread's stack size is then set by the platform (in
// WebAssembly at link time, `-z stack-size`).
pub fn deserializer_pool() -> &'static rayon::ThreadPool {
    static POOL: OnceLock<rayon::ThreadPool> = OnceLock::new();
    POOL.get_or_init(|| {
        rayon::ThreadPoolBuilder::new()
            .stack_size(32 * 1024 * 1024)
            .build()
            .or_else(|_| {
                rayon::ThreadPoolBuilder::new()
                    .num_threads(1)
                    .use_current_thread()
                    .build()
            })
            .expect("failed to build deserializer thread pool")
    })
}
