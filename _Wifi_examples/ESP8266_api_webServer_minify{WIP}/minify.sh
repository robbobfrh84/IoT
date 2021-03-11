echo " !MINIFY CLIENT FOLDER! "

node ../../../_5_node/minifyWebApp/minify.js client/index.html client _resources_images_screenshots/minified/min.html _resources_images_screenshots/minified true

PRE="#define HTML "
HTML=`cat _resources_images_screenshots/minified/min.html`

echo ""
H="$PRE$HTML"
echo "$H"
echo ""

echo $H > server/index.h
