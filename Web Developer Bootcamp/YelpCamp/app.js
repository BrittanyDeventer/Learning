// add express
var express = require("express"),
    app     = express(),
    passport = require("passport"),
    methodOverride = require("method-override"),
    LocalStrategy = require("passport-local"),
    Campground = require("./models/campground"),
    Comment = require("./models/comment"),
    User   = require("./models/user"),
    seedDB = require("./seeds"),
    flash  = require("connect-flash");

//require routes
var commentRoutes    = require("./routes/comments"),
    campgroundRoutes = require("./routes/campgrounds"),
    indexRoutes      = require("./routes/index");

//add and use body parser
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({extended: true}));

// add mongoose
var mongoose = require("mongoose");
// connect mongoose to the db
var url = process.env.DATABASEURL || "mongodb://localhost/yelp_camp";
//mongoose.connect("mongodb://localhost/yelp_camp");
//mongoose.connect("mongodb://britt:Btonni97@ds145752.mlab.com:45752/yelp_camp");
mongoose.connect(url);

console.log(process.env.DATABASEURL);

// add .ejs flag
app.set("view engine", "ejs");

app.use(methodOverride("_method"));

// add custom stylesheets
//console.log(__dirname);
app.use(express.static(__dirname + "/public"));
// use flash
app.use(flash());
//run seeds
// seedDB();

// PASSPORT CONFIGURATION
app.use(require("express-session")({
    secret: "Im amazing",
    resave: false,
    saveUninitialized: false
}));
app.use(passport.initialize());
app.use(passport.session());
passport.use(new LocalStrategy(User.authenticate()));
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());


// pass user and flash message information through to all templates
app.use(function(req, res, next){
    res.locals.currentUser = req.user;
    res.locals.error = req.flash("error");
    res.locals.success = req.flash("success");
    next();
});

// Use routes
app.use("/", indexRoutes);
app.use("/campgrounds", campgroundRoutes);
app.use("/campgrounds/:id/comments", commentRoutes);



// create some generic data
/*Campground.create(
    {
        name: "Bleeper", 
        image: "https://upload.wikimedia.org/wikipedia/commons/8/85/Sky-3.jpg",
        description: "Crazy place.  lots of room."
    }, function(err, campground){
        if(err){
            console.log(err);
        } else {
            console.log("NEW CAMPGROUND ADDED TO DB");
            console.log(campground);
        }
    });*/


//create campgrounds array of campground objects
//var campgrounds = [
  //  {name: "Booger" , image: "https://pixabay.com/get/e83db50a21f4073ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Boob" , image: "https://pixabay.com/get/e83db50a2ff5083ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Bleeper" , image: "https://pixabay.com/get/e83db40e28fd033ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg"},
    //{name: "Booger" , image: "https://pixabay.com/get/e83db50a21f4073ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Boob" , image: "https://pixabay.com/get/e83db50a2ff5083ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Bleeper" , image: "https://pixabay.com/get/e83db40e28fd033ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg"},
    //{name: "Booger" , image: "https://pixabay.com/get/e83db50a21f4073ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Boob" , image: "https://pixabay.com/get/e83db50a2ff5083ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg" },
    //{name: "Bleeper" , image: "https://pixabay.com/get/e83db40e28fd033ed1584d05fb1d4e97e07ee3d21cac104496f5c07aaeecb1bb_340.jpg"},
//];




// add listener
app.listen(process.env.PORT, process.env.IP, function(){
    console.log("YelpCamp has started.");
});