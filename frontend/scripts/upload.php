<?php
require './config.php';
require './huffman.php';

$database = "Toonify";
$table = "Requests";

if(isset($_POST['submit']) && isset($_FILES['image'])){

    // If the image is invalid
    if($_FILES['image']['error'] != 0){
        header("Location: ./../pages/index.php?error=Error: Invalid File");
    } 

    // Extension checking to make sure the image is a PNG
    $extension = explode(".", $_FILES['image']['name'])[1];

    if(strtolower($extension) != "png"){
        header("Location: ./../pages/index.php?error=Error: File must be type PNG, not $extension");
    }

    mysqli_select_db($conn, $database);

    // $imgData = file_get_contents($_FILES['image']['tmp_name']);
    // $imgType = $_FILES['image']['type'];

    // $sql = "INSERT INTO Requests(image) VALUES(?)";
    // $statement = $conn->prepare($sql);
    // $statement->bind_param('s', $imgData);
    // $current_id = $statement->execute() or die("<b>Error:</b><br/>" . mysqli_connect_error());

    $filename = $_FILES['image']['tmp_name'];
    $handle = fopen($filename, "rb"); 
    $fsize = filesize($filename); 
    $contents = fread($handle, $fsize);
    $byteArray = unpack("C*",$contents); 

    $tree = new Huffman($byteArray);

    $dictionary_string = $tree->stringify_dictionary();
    $sql = "INSERT INTO Requests(binary_field, dictionary_field) VALUES('$tree->binary_string', '$dictionary_string')";

    mysqli_query($conn, $sql);

}
?>