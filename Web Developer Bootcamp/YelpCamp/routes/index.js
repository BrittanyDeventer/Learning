var express = require("express");
var router = express.Router();
var User   = require("../models/user");
var passport = require("passport");
var middleware = require("../middleware");


// INDEX
// add landing page
router.get("/", function(req, res){
    res.render("landing");
});

/******************
 * 
 * AUTH ROUTES
 * 
 ******************/

// Show register form
router.get("/register", function(req, res) {
    res.render("register");
});

// Handle sign up logic
router.post("/register", function(req, res) {
    var newUser = new User({username: req.body.username});
    
    User.register(newUser, req.body.password, function(err, user){
        if(err){
            req.flash("error", err.message);
            return res.redirect("/register");
        }
        passport.authenticate("local")(req, res, function(){
            req.flash("success", "Welcome to YelpCamp " + user.username);
            res.redirect("/campgrounds");
        });
    });
});

// Show Login form
router.get("/login", function(req, res) {
    res.render("login");    
});

// Handle login logic
// uses middleware!
// can get rid of empty inline function, just kept it so you could see...
router.post("/login", passport.authenticate("local",
    {
        successRedirect: "/campgrounds",
        failureRedirect: "/login"
    }), function(req, res) {
});

// Add logout route
router.get("/logout", function(req, res) {
    req.logout();
    req.flash("success", "Logged Out!");
    res.redirect("/campgrounds");
});


module.exports = router;