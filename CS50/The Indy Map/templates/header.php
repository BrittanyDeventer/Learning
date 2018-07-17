<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>

        <!-- app's own CSS -->
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>Indy Map: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>Indy Map</title>
        <?php endif ?>

        <!-- app's own JavaScript -->
            <script src="/js/scripts.js"></script>
            
        <!-- http://jquery.com/ -->
            <script src="/js/jquery-1.11.1.min.js"></script> 

        <!-- http://getbootstrap.com/ -->
            <script src="/js/bootstrap.min.js"></script>

        <!-- http://underscorejs.org/ -->
            <script src="/js/underscore-min.js"></script>

        <!-- https://github.com/twitter/typeahead.js/ -->
            <script src="/js/typeahead.jquery.js"></script>
            


    </head>

    <body>
            
        <nav class="navbar navbar-default">
            <div>
              <ul class="nav navbar-nav">
                <li class="active"><a href="index.php">Home</a></li>
                <li><a href="map_form.php">Add a Trip</a></li> <!-- 12/20 These don't work, 404 not found .. because they are controllers and should be in public folder! -->
                <li><a href="map.php">Map</a></li>
              </ul>
            </div>
        </nav>
        
        <div class="container">
        
        <div id="top">
                <h1>The Indy Map: a new way to view your road trips</h1>
        </div>
        
        </br>

        <div id="middle">
