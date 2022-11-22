# PhaseOneConversion

# Build new assets
1. Commit all your changes.
2. Create a new tag: `git tag v0.0.4`
3. Push new tag: `git push origin v0.0.4`
4. This will initiate a new release to be built with the conversion app available inside the assets.

# Running the script
`./conversion <path to input json file> <path to output json file>`

## input json example
Provide a path to a json file that should follow this example format. 
`{
    "paths": [  
       {  
          "input": "images/P0054701.IIQ",
          "outputPendingTiff": "tiff/P0054701.tiff",
          "finalOutput": "final/P0054701.jpg",
          "originalFilename": "P0054701.IIQ",
          "orderId": 1234,
       },
       {  
          "input": "images/P0054702.IIQ",
          "outputPendingTiff": "tiff/P0054702.tiff",
          "finalOutput": "final/P0054702.jpg",
          "originalFilename": "P0054702.IIQ",
          "orderId": 1234,
       }
    ]
 }`
 
 ## output json file
 Provide an path to where the json output will be written to. 
