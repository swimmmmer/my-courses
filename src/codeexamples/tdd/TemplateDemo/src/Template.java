public class Template {
    private String varValue;
    public Template (String text) {
    }
    public void set(String var, String value) {
        this.varValue = value;
    }

    public String evaluate() {
        return "Hello, " + varValue;
    }


}
