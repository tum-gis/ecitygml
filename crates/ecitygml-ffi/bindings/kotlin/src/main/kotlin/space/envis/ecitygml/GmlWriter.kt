package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GmlWriterLib: Library {
    fun ecitygml_GmlWriter_destroy(handle: Pointer)
    fun ecitygml_GmlWriter_new(format: Int): Pointer
    fun ecitygml_GmlWriter_from_path(path: Slice): ResultPointerPointer
    fun ecitygml_GmlWriter_from_base_path_with_format(basePath: Slice, format: Int): ResultPointerPointer
    fun ecitygml_GmlWriter_with_formatting(handle: Pointer, formatting: Pointer): Unit
    fun ecitygml_GmlWriter_finish(handle: Pointer, cityModel: Pointer): ResultUnitPointer
    fun ecitygml_GmlWriter_data(handle: Pointer): Slice
}
/** Writes CityGML to a file or to memory. Rust's builder methods take the writer by value and
*`finish` consumes it, which Diplomat can't express: here they modify it in place, and
*`finish` can be called only once.
*/
class GmlWriter internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class GmlWriterCleaner(val handle: Pointer, val lib: GmlWriterLib) : Runnable {
        override fun run() {
            lib.ecitygml_GmlWriter_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, GmlWriter.GmlWriterCleaner(handle, GmlWriter.lib));
    }

    companion object {
        internal val libClass: Class<GmlWriterLib> = GmlWriterLib::class.java
        internal val lib: GmlWriterLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** Writes CityGML of the given `format` to memory, e.g. in WebAssembly, where there is no
        *file system; read it with `data` after `finish`. Not in Python (see `data`).
        */
        fun create(format: CitygmlFormat): GmlWriter {
            
            val returnVal = lib.ecitygml_GmlWriter_new(format.toNative());
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = GmlWriter(handle, selfEdges, true)
            return returnOpaque
        }
        @JvmStatic
        
        /** Creates (or truncates) the file at `path`; its extension (`.gml`, `.gml.gz` or
        *`.gml.zst`) sets the format.
        */
        fun fromPath(path: String): Result<GmlWriter> {
            val pathSliceMemory = PrimitiveArrayTools.borrowUtf8(path)
            
            val returnVal = lib.ecitygml_GmlWriter_from_path(pathSliceMemory.slice);
            try {
                val nativeOkVal = returnVal.getNativeOk();
                if (nativeOkVal != null) {
                    val selfEdges: List<Any> = listOf()
                    val handle = nativeOkVal 
                    val returnOpaque = GmlWriter(handle, selfEdges, true)
                    return returnOpaque.ok()
                } else {
                    val selfEdges: List<Any> = listOf()
                    val handle = returnVal.getNativeErr()!! 
                    val returnOpaque = Error(handle, selfEdges, true)
                    return returnOpaque.err()
                }
            } finally {
                pathSliceMemory.close()
            }
        }
        @JvmStatic
        
        /** Creates (or truncates) the file `<base_path>.<extension of format>`.
        */
        fun fromBasePathWithFormat(basePath: String, format: CitygmlFormat): Result<GmlWriter> {
            val basePathSliceMemory = PrimitiveArrayTools.borrowUtf8(basePath)
            
            val returnVal = lib.ecitygml_GmlWriter_from_base_path_with_format(basePathSliceMemory.slice, format.toNative());
            try {
                val nativeOkVal = returnVal.getNativeOk();
                if (nativeOkVal != null) {
                    val selfEdges: List<Any> = listOf()
                    val handle = nativeOkVal 
                    val returnOpaque = GmlWriter(handle, selfEdges, true)
                    return returnOpaque.ok()
                } else {
                    val selfEdges: List<Any> = listOf()
                    val handle = returnVal.getNativeErr()!! 
                    val returnOpaque = Error(handle, selfEdges, true)
                    return returnOpaque.err()
                }
            } finally {
                basePathSliceMemory.close()
            }
        }
    }
    
    /** How the GML is laid out (default: `Formatting::new_line`). Has no effect after `finish`.
    */
    fun withFormatting(formatting: Formatting): Unit {
        
        val returnVal = lib.ecitygml_GmlWriter_with_formatting(handle, formatting.handle);
        
    }
    
    /** Writes the city model; fails with `InvalidArgument` if called a second time.
    */
    fun finish(cityModel: CityModel): Result<Unit> {
        
        val returnVal = lib.ecitygml_GmlWriter_finish(handle, cityModel.handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            return Unit.ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    /** What a writer created with `new` has written (empty before `finish`, and for files).
    *Not in Rust, where the caller keeps the writer it passes to `GmlWriter::new`. Not in
    *Python: Diplomat's nanobind backend returns byte slices as NumPy arrays, and without NumPy
    *the conversion aborts the interpreter; Python writes files with `from_path` instead.
    */
    fun data(): UByteArray {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GmlWriter_data(handle);
            return PrimitiveArrayTools.getUByteArray(returnVal)
    }

}