public enum Encoding {

    JPG,

    BMP,

    GIF,

    PNG;

    /**
     * Returns the enum in lowercase.
     */
    public String toString() {
        String id = name();
        return id.toLowerCase();
    }
}