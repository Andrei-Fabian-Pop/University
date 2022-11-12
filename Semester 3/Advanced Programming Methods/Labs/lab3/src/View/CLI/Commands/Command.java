package View.CLI.Commands;

public abstract class Command {
    private final String key;
    private final String description;

    protected Command(String key, String description) {
        this.key = key;
        this.description = description;
    }

    public abstract void execute();

    public String getKey() {
        return this.key;
    }

    public String getDescription() {
        return this.description;
    }
}
