<?php
require './config.php';

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

    $imgData = file_get_contents($_FILES['image']['tmp_name']);
    $imgType = $_FILES['image']['type'];

    $sql = "INSERT INTO Requests(image) VALUES(?)";
    $statement = $conn->prepare($sql);
    $statement->bind_param('s', $imgData);
    $current_id = $statement->execute() or die("<b>Error:</b> Problem on Image Insert<br/>" . mysqli_connect_error());

    $filename = $_FILES['image']['tmp_name'];
    $handle = fopen($filename, "rb"); 
    $fsize = filesize($filename); 
    $contents = fread($handle, $fsize);
    $byteArray = unpack("C*",$contents); 
    
    for($n = 1; $n < 10; $n++)
    { 
        echo $byteArray[$n].'<br/>'; 
    }

}
?>

<?php 

// if (isset($_POST['submit']) && isset($_FILES['my_image'])) {
// 	include "db_conn.php";

// 	echo "<pre>";
// 	print_r($_FILES['my_image']);
// 	echo "</pre>";

// 	$img_name = $_FILES['my_image']['name'];
// 	$img_size = $_FILES['my_image']['size'];
// 	$tmp_name = $_FILES['my_image']['tmp_name'];
// 	$error = $_FILES['my_image']['error'];

// 	if ($error === 0) {
// 		if ($img_size > 125000) {
// 			$em = "Sorry, your file is too large.";
// 		    header("Location: index.php?error=$em");
// 		}else {
// 			$img_ex = pathinfo($img_name, PATHINFO_EXTENSION);
// 			$img_ex_lc = strtolower($img_ex);

// 			$allowed_exs = array("jpg", "jpeg", "png"); 

// 			if (in_array($img_ex_lc, $allowed_exs)) {
// 				$new_img_name = uniqid("IMG-", true).'.'.$img_ex_lc;
// 				$img_upload_path = 'uploads/'.$new_img_name;
// 				move_uploaded_file($tmp_name, $img_upload_path);

// 				// Insert into Database
// 				$sql = "INSERT INTO images(image_url) 
// 				        VALUES('$new_img_name')";
// 				mysqli_query($conn, $sql);
// 				header("Location: view.php");
// 			}else {
// 				$em = "You can't upload files of this type";
// 		        header("Location: index.php?error=$em");
// 			}
// 		}
// 	}else {
// 		$em = "unknown error occurred!";
// 		header("Location: index.php?error=$em");
// 	}

// }else {
// 	header("Location: index.php");
// }

?>