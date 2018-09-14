var mongoose = require("mongoose");

var commentSchema = mongoose.Schema({
    text: String,
    author: {
        id : {
            type: mongoose.Schema.Types.ObjectId,
            ref: "User"
        },
        username: String  // better to store this here rather than look up the username every time a comment is created.
    }
});

module.exports = mongoose.model("Comment", commentSchema);