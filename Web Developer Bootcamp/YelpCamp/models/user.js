var mongoose = require("mongoose");
var passportLocalMongoose = require("passport-local-mongoose");


var UserSchema = new mongoose.Schema({
    username: String,
    password: String
});

//add all methods from passport-local-mongoose to this schema
UserSchema.plugin(passportLocalMongoose);

module.exports = mongoose.model("User", UserSchema);