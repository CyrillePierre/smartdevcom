package com.example.hellojni.json.commands;

/**
 * Created by toto on 23/02/16.
 */
public class VoiceCommand {
    private Command command;

    public VoiceCommand(Command command) {
        this.command = command;
    }

    public Command getCommand() {
        return command;
    }
}
