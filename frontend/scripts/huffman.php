<?php

class Huffman {

    protected $root = null;

    protected $source_array;
    
    function __construct($array){
        $frequency_map = array();
        
        $keys = array_keys($array);

        for($i = 0; $i < sizeof($array); $i++){
            if(!array_key_exists($array[$keys[i]], $frequency_map)){
                $frequency = 0;
                for($j = $i; $j < sizeof($array); $j++){
                    if($array[$keys[$j]] == $array[$keys[$i]]) $frequency++;
                }

                $frequency_map[$array[$keys[$i]]] = $frequency;
            }
        }
        // foreach($array as $key => $value){
        //     if(!array_key_exists($value, $frequency_map)){
        //         $frequency = 0;
        //         foreach($array as $second_key => $second_value){
        //             if($value == $second_value) $frequency++;
        //         }

        //         $frequency_map[$value] = $frequency
        //     }
        // }

        
        
        $this->makeTree($frequency);
    }
	
    
	


}

class HuffmanNode {

    
    public $value;

    public $frequency;
	
    public $left = null;
    
    public $right = null;

    function __construct($value, $frequency) {
        $this->value = $value;
        $this->weight = $frequency;
    }

    function isLeaf() {
        return ($this->left == null && $this->right == null);
    }
	
}

?>
