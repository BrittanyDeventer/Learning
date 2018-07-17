        <!-- https://developers.google.com/maps/documentation/javascript/ -->
        <script src="https://maps.googleapis.com/maps/api/js"></script>
        
        <!-- http://google-maps-utility-library-v3.googlecode.com/svn/tags/markerwithlabel/1.1.9/ -->
        <script src="/js/markerwithlabel_packed.js"></script>    
        
        <!-- app's own JavaScript -->
        <script src="/js/scripts.js"></script>  
      
        <!-- fill viewport -->
        <div class="container-fluid">

            <!-- https://developers.google.com/maps/documentation/javascript/tutorial -->
            <div id="map-canvas"></div>

            <!-- http://getbootstrap.com/css/#forms -->
            <form class="form-inline" id="form" role="form">
                <div class="form-group">
                    <label class="sr-only" for="q">City, State, Postal Code</label>
                    <input class="form-control" id="q" placeholder="City, State, Postal Code" type="text"/>
                </div>
            </form>
        </div>
