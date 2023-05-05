<?php
  require '../scripts/config.php';

  $database = "Toonify";
  $sql = "CREATE DATABASE if not exists $database";
  mysqli_query($conn,$sql);

  mysqli_select_db($conn, $database);
  $sql = "CREATE TABLE if not exists Requests (
          id int(11) NOT NULL AUTO_INCREMENT,
          binary_field LONGTEXT NOT NULL,
          dictionary_field LONGTEXT NOT NULL,
          PRIMARY KEY (id)
      )";

  if (!mysqli_query($conn,$sql) === TRUE) {
  echo "Error creating table: " . $conn->error;
  }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <script src="https://kit.fontawesome.com/185669591d.js" crossorigin="anonymous"></script>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet"  href="../css/main.css?<?=time()?>">
    <title>Toonify</title>
</head>
<body>
<form action="../scripts/upload.php?>" method="post" enctype="multipart/form-data">
    <div class="container">
        <h1>Toonify </h1>
        <p>With Toonify, we'll take your images and make them into intricate cartoonified images — all with just a few clicks. To start, just upload a file of type png or jpeg and hit Toonify! We'll take care of the rest and you'll see the toonified version pop up just a few moments later❗</p>
        <div class = "buttons">              
              <label class="custom-file-upload">
                  <input type="file" name="image">
                  Upload
                  <i class="fa fa-cloud-upload" id="upload-icon" aria-hidden="true"></i>
              </label>
              <input class="custom-file-upload" type="submit" value="Toonify!" name="submit" />

              <?php 
                if (isset($_GET['error'])){
                  echo "<p id=\"error-message\">";
                  echo $_GET['error'];
                  echo "</p>";
                } 
              ?>
        </div>
    </div>
    </form> 
</body>
</html>
