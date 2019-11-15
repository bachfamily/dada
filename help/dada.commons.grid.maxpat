{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 0,
			"revision" : 5,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 84.0, 129.0, 640.0, 480.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"patching_rect" : [ 305.0, 407.5, 313.0, 22.0 ],
					"text" : "dada.base dadacommondbhelp winterdb.txt @readonly 1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-60",
					"linecount" : 6,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 521.5, 112.5, 115.0, 98.0 ],
					"text" : "Use the slider and see how the horizontal lines in the grid change with automatic grid"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-102",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 412.5, 54.0, 223.0, 25.0 ],
					"text" : "Only works with gridmode=\"Fixed\""
				}

			}
, 			{
				"box" : 				{
					"attr" : "gridstep",
					"id" : "obj-101",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 231.0, 54.0, 186.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "gridlabelscolor",
					"id" : "obj-96",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 383.0, 104.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "gridcolor",
					"id" : "obj-94",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 383.0, 78.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "showgridlabels",
					"id" : "obj-82",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 29.0, 102.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "showgrid",
					"id" : "obj-77",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 19.0, 78.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "gridmode",
					"id" : "obj-69",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 3.0, 54.0, 225.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "gridlabelsfontsize",
					"id" : "obj-63",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 185.02154541015625, 78.0, 183.0, 22.0 ],
					"text_width" : 118.0
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-59",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 448.0, 216.0, 50.0, 22.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_invisible" : 1,
							"parameter_shortname" : "number",
							"parameter_type" : 3,
							"parameter_longname" : "number"
						}

					}
,
					"varname" : "number"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-57",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 388.0, 181.0, 147.0, 22.0 ],
					"text" : "expr pow(10.\\,($f1-64.)/32)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-56",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 388.0, 216.0, 55.0, 22.0 ],
					"text" : "zoom $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-54",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 388.0, 154.0, 140.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_shortname" : "slider",
							"parameter_type" : 0,
							"parameter_longname" : "slider"
						}

					}
,
					"varname" : "slider"
				}

			}
, 			{
				"box" : 				{
					"center" : [ -712.745347807499911, -5345.375 ],
					"colorfield" : "tonalcentroid5th",
					"convexcombmax" : [ 1.0 ],
					"convexcombmin" : [ 0.0 ],
					"database" : "dadacommondbhelp",
					"id" : "obj-53",
					"maxclass" : "dada.cartesian",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 4,
					"out" : "nnn",
					"outlettype" : [ "", "", "", "bang" ],
					"patching_rect" : [ 388.0, 248.0, 241.0, 136.0 ],
					"query" : "SELECT * FROM scores",
					"shapefield" : "filename",
					"sizefield" : "loudness",
					"table" : "scores",
					"versionnumber" : 10200,
					"vzoom" : 0.66678923821781,
					"xfield" : "spread",
					"yfield" : "centroid",
					"zoom" : 3.059264009486175
				}

			}
, 			{
				"box" : 				{
					"center" : [ -712.745347807499911, -5345.375 ],
					"colorfield" : "tonalcentroid5th",
					"convexcombmax" : [ 1.0 ],
					"convexcombmin" : [ 0.0 ],
					"database" : "dadacommondbhelp",
					"id" : "obj-33",
					"maxclass" : "dada.cartesian",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 4,
					"out" : "nnn",
					"outlettype" : [ "", "", "", "bang" ],
					"patching_rect" : [ 3.0, 134.0, 365.02154541015625, 251.0 ],
					"query" : "SELECT * FROM scores",
					"shapefield" : "filename",
					"sizefield" : "loudness",
					"table" : "scores",
					"versionnumber" : 10200,
					"vzoom" : 1.230618373475517,
					"xfield" : "spread",
					"yfield" : "centroid",
					"zoom" : 4.633598657926616
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.0, 3.0, 626.0, 47.0 ],
					"text" : "Most dada objects support display of grid and labels. By default the grid will have lines displayed according to the current level of (horizontal or vertical) zoom. This corresponds to the \"automatic\" grid mode. You can also set the grid to a fixed number by choosing \"fixed\" as grid mode, and setting the grid step values via the gridstep attribute.",
					"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-101", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-57", 0 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 0 ],
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-56", 0 ],
					"order" : 1,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-59", 0 ],
					"order" : 0,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-77", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-94", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-96", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-59" : [ "number", "number", 0 ],
			"obj-54" : [ "slider", "slider", 0 ],
			"parameterbanks" : 			{

			}

		}
,
		"dependency_cache" : [ 			{
				"name" : "dada.cartesian.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.base.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0
	}

}
