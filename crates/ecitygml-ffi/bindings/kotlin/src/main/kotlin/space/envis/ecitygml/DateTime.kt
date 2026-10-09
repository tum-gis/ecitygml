package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface DateTimeLib: Library {
    fun ecitygml_DateTime_destroy(handle: Pointer)
    fun ecitygml_DateTime_from_parts(year: Int, month: FFIUint32, day: FFIUint32, hour: FFIUint32, minute: FFIUint32, second: FFIUint32, nanosecond: FFIUint32, offsetSeconds: Int): ResultPointerPointer
    fun ecitygml_DateTime_year(handle: Pointer): Int
    fun ecitygml_DateTime_month(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_day(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_hour(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_minute(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_second(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_nanosecond(handle: Pointer): FFIUint32
    fun ecitygml_DateTime_offset_seconds(handle: Pointer): Int
    fun ecitygml_DateTime_to_rfc3339(handle: Pointer, write: Pointer): Unit
    fun ecitygml_DateTime_timestamp(handle: Pointer): Long
    fun ecitygml_DateTime_timestamp_subsec_nanos(handle: Pointer): FFIUint32
}
/** A date and time of day with a timezone, created or borrowed from a city model.
*/
class DateTime internal constructor (
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

    private class DateTimeCleaner(val handle: Pointer, val lib: DateTimeLib) : Runnable {
        override fun run() {
            lib.ecitygml_DateTime_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, DateTime.DateTimeCleaner(handle, DateTime.lib));
    }

    companion object {
        internal val libClass: Class<DateTimeLib> = DateTimeLib::class.java
        internal val lib: DateTimeLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** Creates a date-time from its local fields and the offset east of UTC in seconds; fails with
        *`InvalidArgument` for invalid fields or offsets.
        */
        fun fromParts(year: Int, month: UInt, day: UInt, hour: UInt, minute: UInt, second: UInt, nanosecond: UInt, offsetSeconds: Int): Result<DateTime> {
            
            val returnVal = lib.ecitygml_DateTime_from_parts(year, FFIUint32(month), FFIUint32(day), FFIUint32(hour), FFIUint32(minute), FFIUint32(second), FFIUint32(nanosecond), offsetSeconds);
            val nativeOkVal = returnVal.getNativeOk();
            if (nativeOkVal != null) {
                val selfEdges: List<Any> = listOf()
                val handle = nativeOkVal 
                val returnOpaque = DateTime(handle, selfEdges, true)
                return returnOpaque.ok()
            } else {
                val selfEdges: List<Any> = listOf()
                val handle = returnVal.getNativeErr()!! 
                val returnOpaque = Error(handle, selfEdges, true)
                return returnOpaque.err()
            }
        }
    }
    
    fun year(): Int {
        
        val returnVal = lib.ecitygml_DateTime_year(handle);
        return (returnVal)
    }
    
    /** 1 to 12.
    */
    fun month(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_month(handle);
        return (returnVal.toUInt())
    }
    
    /** 1 to 31.
    */
    fun day(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_day(handle);
        return (returnVal.toUInt())
    }
    
    fun hour(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_hour(handle);
        return (returnVal.toUInt())
    }
    
    fun minute(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_minute(handle);
        return (returnVal.toUInt())
    }
    
    fun second(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_second(handle);
        return (returnVal.toUInt())
    }
    
    fun nanosecond(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_nanosecond(handle);
        return (returnVal.toUInt())
    }
    
    /** The UTC offset in seconds (local time minus UTC), e.g. 3600 for `+01:00`.
    */
    fun offsetSeconds(): Int {
        
        val returnVal = lib.ecitygml_DateTime_offset_seconds(handle);
        return (returnVal)
    }
    
    /** RFC 3339 / ISO 8601 representation, e.g. `2017-01-23T00:00:00+01:00` (via `as_chrono()`;
    *egml has no lexical form yet).
    */
    fun toRfc3339(): String {
        val write = DW.lib.diplomat_buffer_write_create(0)
        val returnVal = lib.ecitygml_DateTime_to_rfc3339(handle, write);
        
        val returnString = DW.writeToString(write)
        return returnString
    }
    
    /** Seconds since the Unix epoch (1970-01-01T00:00:00Z) (via `as_chrono()`).
    */
    fun timestamp(): Long {
        
        val returnVal = lib.ecitygml_DateTime_timestamp(handle);
        return (returnVal)
    }
    
    /** Nanoseconds beyond the full seconds of `timestamp` (via `as_chrono()`).
    */
    fun timestampSubsecNanos(): UInt {
        
        val returnVal = lib.ecitygml_DateTime_timestamp_subsec_nanos(handle);
        return (returnVal.toUInt())
    }

}