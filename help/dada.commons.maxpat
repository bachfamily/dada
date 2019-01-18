{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 0,
			"revision" : 2,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 34.0, 118.0, 791.0, 666.0 ],
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
					"id" : "obj-11",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 671.0, 162.0, 82.0, 22.0 ],
					"text" : "offset 0 -3000"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-10",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 689.0, 124.0, 84.0, 22.0 ],
					"text" : "offset 0 -2400"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-1",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 696.0, 96.0, 84.0, 22.0 ],
					"text" : "offset 0 -1800"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 696.0, 51.0, 84.0, 22.0 ],
					"text" : "offset 0 -1200"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 602.0, 51.0, 77.0, 22.0 ],
					"text" : "offset 0 -600"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 7,
					"numoutlets" : 7,
					"outlettype" : [ "bang", "bang", "bang", "bang", "bang", "bang", "" ],
					"patching_rect" : [ 518.0, 2.0, 84.0, 22.0 ],
					"text" : "sel 0 1 2 3 4 5"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-3",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 518.0, 51.0, 60.0, 22.0 ],
					"text" : "offset 0 0"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-9",
					"maxclass" : "tab",
					"mode" : 1,
					"multiline" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 68.567626953125, 568.0, 28.0 ],
					"segmented" : 1,
					"tabs" : [ "Zoom, center, domain, range", "Grid", "Record into bach.roll", "Export as image", "To Jitter", "To Mira" ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 113.0, 34.5, 361.0, 21.0 ],
					"text" : ": some features common to all (or most) UI objects",
					"textcolor" : [ 0.50196099281311, 0.50196099281311, 0.50196099281311, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 1,
					"clickthrough" : 0,
					"embed" : 1,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-8",
					"lockeddragscroll" : 0,
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 0,
							"revision" : 2,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 459.0, 185.0, 893.0, 522.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-60",
									"linecount" : 6,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 533.5, 3119.5, 117.0, 98.0 ],
									"text" : "Use the slider and see how the horizontal lines in the grid change with automatic grid"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-102",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 424.5, 3061.0, 223.0, 25.0 ],
									"text" : "Only works with gridmode=\"Fixed\""
								}

							}
, 							{
								"box" : 								{
									"attr" : "gridstep",
									"id" : "obj-101",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 243.0, 3061.0, 186.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "gridlabelscolor",
									"id" : "obj-96",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 395.0, 3111.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "gridcolor",
									"id" : "obj-94",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 395.0, 3085.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "showgridlabels",
									"id" : "obj-82",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 41.0, 3109.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "showgrid",
									"id" : "obj-77",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 31.0, 3085.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "gridmode",
									"id" : "obj-69",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 3061.0, 225.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "gridlabelsfontsize",
									"id" : "obj-63",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 197.02154541015625, 3085.0, 183.0, 22.0 ],
									"text_width" : 118.0
								}

							}
, 							{
								"box" : 								{
									"format" : 6,
									"id" : "obj-59",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 460.0, 3223.0, 50.0, 22.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
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
, 							{
								"box" : 								{
									"id" : "obj-57",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 400.0, 3188.0, 147.0, 22.0 ],
									"text" : "expr pow(10.\\,($f1-64.)/32)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-56",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 400.0, 3223.0, 55.0, 22.0 ],
									"text" : "zoom $1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "slider",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 400.0, 3161.0, 140.0, 15.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_shortname" : "slider",
											"parameter_type" : 0,
											"parameter_longname" : "slider"
										}

									}
,
									"varname" : "slider"
								}

							}
, 							{
								"box" : 								{
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
									"patching_rect" : [ 400.0, 3255.0, 241.0, 136.0 ],
									"query" : "SELECT * FROM scores",
									"shapefield" : "filename",
									"sizefield" : "loudness",
									"table" : "scores",
									"versionnumber" : 10000,
									"vzoom" : 1.0,
									"xfield" : "spread",
									"yfield" : "centroid",
									"zoom" : 3.059264009486175
								}

							}
, 							{
								"box" : 								{
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
									"patching_rect" : [ 15.0, 3141.0, 365.02154541015625, 251.0 ],
									"query" : "SELECT * FROM scores",
									"shapefield" : "filename",
									"sizefield" : "loudness",
									"table" : "scores",
									"versionnumber" : 10000,
									"vzoom" : 1.230618373475517,
									"xfield" : "spread",
									"yfield" : "centroid",
									"zoom" : 4.633598657926616
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-32",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 3010.0, 626.0, 47.0 ],
									"text" : "Most dada objects support display of grid and labels. By default the grid will have lines displayed according to the current level of (horizontal or vertical) zoom. This corresponds to the \"automatic\" grid mode. You can also set the grid to a fixed number by choosing \"fixed\" as grid mode, and setting the grid step values via the gridstep attribute.",
									"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-99",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 2402.5, 80.5, 40.0 ],
									"text" : "Play and record"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-98",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 126.5, 2406.0, 483.0, 33.0 ],
									"text" : "While playing, have bach.transcribe receive the content of the dada object's Playout in order to record the  result in a bach.roll",
									"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-97",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 510.0, 2627.0, 66.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.flat 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-93",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 510.0, 2597.0, 107.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.keys content"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-91",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "float" ],
									"patching_rect" : [ 436.0, 2658.0, 93.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.transcribe"
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 80001,
									"clefs" : [ "G", "G", "F" ],
									"defaultnoteslots" : [ "null" ],
									"enharmonictable" : [ "default", "default", "default" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidevoices" : [ 0, 0, 0 ],
									"id" : "obj-92",
									"keys" : [ "CM", "CM", "CM" ],
									"loop" : [ 0.0, 1000.0 ],
									"maxclass" : "bach.roll",
									"midichannels" : [ 1, 1, 3 ],
									"numinlets" : 6,
									"numoutlets" : 8,
									"numparts" : [ 1, 1, 1 ],
									"numvoices" : 3,
									"out" : "nnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 436.0, 2689.0, 194.0, 102.5 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5, 5, 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80002,
									"voicenames" : [ "[", "]", "[", "]", "[", "]" ],
									"voicespacing" : [ 0.0, 17.0, 17.0, 17.0 ],
									"whole_roll_data_0000000000" : [ "roll", "[", "slotinfo", "[", 1, "[", "name", "velocity envelope", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 2, "[", "name", "slot function", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 3, "[", "name", "slot intlist", "]", "[", "type", "intlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 4, "[", "name", "slot floatlist", "]", "[", "type", "floatlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 5, "[", "name", "slot int", "]", "[", "type", "int", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 6, "[", "name", "slot float", "]", "[", "type", "float", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 7, "[", "name", "slot text", "]", "[", "type", "text", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 8, "[", "name", "slot filelist", "]", "[", "type", "filelist", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 9, "[", "name", "slot spat", "]", "[", "type", "spat", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 10, "[", "name", "slot llll", "]", "[", "type", "llll", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 11, "[", "name", "slot 11", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 12, "[", "name", "slot 12", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 13, "[", "name", "slot 13", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 14, "[", "name", "slot 14", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 15, "[", "name", "slot 15", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 16, "[", "name", "slot 16", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 17, "[", "name", "slot 17", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 18, "[", "name", "slot 18", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 19, "[", "name", "slot 19", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 20, "[", "name", "dynamics", "]", "[", "type", "dynamics", "]", "[", "key", "d", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 21, "[", "name", "lyrics", "]", "[", "type", "text", "]", "[", "key", "l", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 22, "[", "name", "articulations", "]", "[", "type", "articulations", "]", "[", "key", "a", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 23, "[", "name", "notehead", "]", "[", "type", "notehead", "]", "[", "key", "h", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 24, "[", "name", "slot 24", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 25, "[", "name", "slot 25", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 26, "[", "name", "slot 26", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 27, "[", "name", "slot 27", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 28, "[", "name", "slot 28", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 29, "[", "name", "slot 29", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 30, "[", "name", "slot 30", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "]", "[", "commands", "[", 1, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 2, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 3, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 4, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 5, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "]", "[", "groups", "]", "[", "markers", "]", "[", "midichannels", 1, 1, 3, "]", "[", "articulationinfo", "]", "[", "noteheadinfo", "]", "[", 0, "]", "[", 0, "]", "[", 0, "]" ],
									"whole_roll_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-90",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "float" ],
									"patching_rect" : [ 237.0, 2660.0, 148.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.transcribe"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-89",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "float" ],
									"patching_rect" : [ 15.0, 2660.0, 166.5, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.transcribe"
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 80001,
									"clefs" : [ "G", "G" ],
									"defaultnoteslots" : [ "null" ],
									"enharmonictable" : [ "default", "default" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidevoices" : [ 0, 0 ],
									"id" : "obj-88",
									"keys" : [ "CM", "CM" ],
									"loop" : [ 0.0, 1000.0 ],
									"maxclass" : "bach.roll",
									"midichannels" : [ 1, 1 ],
									"numinlets" : 6,
									"numoutlets" : 8,
									"numparts" : [ 1, 1 ],
									"numvoices" : 2,
									"out" : "nnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 237.0, 2691.0, 191.0, 93.666667000000004 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5, 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80002,
									"voicenames" : [ "[", "]", "[", "]" ],
									"voicespacing" : [ -9.0, 6.5, 17.0 ],
									"whole_roll_data_0000000000" : [ "roll", "[", "slotinfo", "[", 1, "[", "name", "velocity envelope", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 2, "[", "name", "slot function", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 3, "[", "name", "slot intlist", "]", "[", "type", "intlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 4, "[", "name", "slot floatlist", "]", "[", "type", "floatlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 5, "[", "name", "slot int", "]", "[", "type", "int", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 6, "[", "name", "slot float", "]", "[", "type", "float", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 7, "[", "name", "slot text", "]", "[", "type", "text", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 8, "[", "name", "slot filelist", "]", "[", "type", "filelist", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 9, "[", "name", "slot spat", "]", "[", "type", "spat", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 10, "[", "name", "slot llll", "]", "[", "type", "llll", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 11, "[", "name", "slot 11", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 12, "[", "name", "slot 12", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 13, "[", "name", "slot 13", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 14, "[", "name", "slot 14", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 15, "[", "name", "slot 15", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 16, "[", "name", "slot 16", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 17, "[", "name", "slot 17", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 18, "[", "name", "slot 18", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 19, "[", "name", "slot 19", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 20, "[", "name", "dynamics", "]", "[", "type", "dynamics", "]", "[", "key", "d", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 21, "[", "name", "lyrics", "]", "[", "type", "text", "]", "[", "key", "l", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 22, "[", "name", "articulations", "]", "[", "type", "articulations", "]", "[", "key", "a", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 23, "[", "name", "notehead", "]", "[", "type", "notehead", "]", "[", "key", "h", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 24, "[", "name", "slot 24", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 25, "[", "name", "slot 25", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 26, "[", "name", "slot 26", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 27, "[", "name", "slot 27", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 28, "[", "name", "slot 28", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 29, "[", "name", "slot 29", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 30, "[", "name", "slot 30", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "]", "[", "commands", "[", 1, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 2, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 3, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 4, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 5, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "]", "[", "groups", "]", "[", "markers", "]", "[", "midichannels", 1, 1, "]", "[", "articulationinfo", "]", "[", "noteheadinfo", "]", "[", 0, "]", "[", 0, "]" ],
									"whole_roll_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 80001,
									"defaultnoteslots" : [ "null" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-87",
									"loop" : [ 0.0, 1000.0 ],
									"maxclass" : "bach.roll",
									"numinlets" : 6,
									"numoutlets" : 8,
									"numvoices" : 1,
									"out" : "nnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 15.0, 2691.0, 193.0, 73.0 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80002,
									"voicenames" : [ "[", "]" ],
									"voicespacing" : [ 0.0, 17.0 ],
									"whole_roll_data_0000000000" : [ "roll", "[", "slotinfo", "[", 1, "[", "name", "velocity envelope", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 2, "[", "name", "slot function", "]", "[", "type", "function", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "grid", "]", "[", "ysnap", "]", "[", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 3, "[", "name", "slot intlist", "]", "[", "type", "intlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 4, "[", "name", "slot floatlist", "]", "[", "type", "floatlist", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 5, "[", "name", "slot int", "]", "[", "type", "int", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 6, "[", "name", "slot float", "]", "[", "type", "float", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 7, "[", "name", "slot text", "]", "[", "type", "text", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 8, "[", "name", "slot filelist", "]", "[", "type", "filelist", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 9, "[", "name", "slot spat", "]", "[", "type", "spat", "]", "[", "key", 0, "]", "[", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "representation", "]", "[", "temporalmode", "relative", "]", "[", "extend", 0, "]", "[", "width", "auto", "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 10, "[", "name", "slot llll", "]", "[", "type", "llll", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 11, "[", "name", "slot 11", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 12, "[", "name", "slot 12", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 13, "[", "name", "slot 13", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 14, "[", "name", "slot 14", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 15, "[", "name", "slot 15", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 16, "[", "name", "slot 16", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 17, "[", "name", "slot 17", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 18, "[", "name", "slot 18", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 19, "[", "name", "slot 19", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 20, "[", "name", "dynamics", "]", "[", "type", "dynamics", "]", "[", "key", "d", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 21, "[", "name", "lyrics", "]", "[", "type", "text", "]", "[", "key", "l", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 0, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 22, "[", "name", "articulations", "]", "[", "type", "articulations", "]", "[", "key", "a", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 23, "[", "name", "notehead", "]", "[", "type", "notehead", "]", "[", "key", "h", "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 24, "[", "name", "slot 24", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 25, "[", "name", "slot 25", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 26, "[", "name", "slot 26", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 27, "[", "name", "slot 27", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 28, "[", "name", "slot 28", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 29, "[", "name", "slot 29", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "[", 30, "[", "name", "slot 30", "]", "[", "type", "none", "]", "[", "key", 0, "]", "[", "temporalmode", "none", "]", "[", "extend", 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "height", "auto", "]", "[", "copywhensplit", 1, "]", "[", "access", "readandwrite", "]", "[", "follownotehead", 0, "]", "]", "]", "[", "commands", "[", 1, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 2, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 3, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 4, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "[", 5, "[", "note", "note", "]", "[", "chord", "chord", "]", "[", "rest", "rest", "]", "[", "key", 0, "]", "]", "]", "[", "groups", "]", "[", "markers", "]", "[", "midichannels", 1, "]", "[", "articulationinfo", "]", "[", "noteheadinfo", "]", "[", 0, "]" ],
									"whole_roll_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-86",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 15.0, 2410.0, 24.0, 24.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_invisible" : 1,
											"parameter_shortname" : "toggle[1]",
											"parameter_type" : 3,
											"parameter_longname" : "toggle[1]"
										}

									}
,
									"varname" : "toggle[1]"
								}

							}
, 							{
								"box" : 								{
									"center" : [ -712.745347807499911, -5345.375 ],
									"colorfield" : "tonalcentroid5th",
									"convexcombmax" : [ 1.0 ],
									"convexcombmin" : [ 0.0 ],
									"database" : "dadacommondbhelp",
									"id" : "obj-61",
									"maxclass" : "dada.cartesian",
									"mode" : 0,
									"numinlets" : 1,
									"numoutlets" : 4,
									"out" : "nnn",
									"outlettype" : [ "", "", "", "bang" ],
									"patching_rect" : [ 436.0, 2453.0, 203.021545000000003, 127.0 ],
									"query" : "SELECT * FROM scores",
									"shapefield" : "filename",
									"sizefield" : "loudness",
									"table" : "scores",
									"versionnumber" : 10000,
									"vzoom" : 1.0,
									"xfield" : "spread",
									"yfield" : "centroid",
									"zoom" : 2.577163924351775
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "[", "room", "[", "vertices", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 393870936, 3225768614, "_x_x_x_x_bach_float64_x_x_x_x_", 816601484, 3226604335, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1780115129, 3225802520, "_x_x_x_x_bach_float64_x_x_x_x_", 2499577158, 1078522673, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2769923502, 1077367865, "_x_x_x_x_bach_float64_x_x_x_x_", 3507199166, 1078096279, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2769923502, 1077367865, "_x_x_x_x_bach_float64_x_x_x_x_", 237488823, 1079541046, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2839323296, 3226576867, "_x_x_x_x_bach_float64_x_x_x_x_", 237488823, 1079541046, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "[", "edges", "[", 1, 2, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 2, 3, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 3, 4, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 4, 1, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 5, 6, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 6, 7, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 7, 8, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 8, 5, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "]", "[", "balls", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 587227469, 3223543506, "_x_x_x_x_bach_float64_x_x_x_x_", 1778886370, 3223766076, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 89434243, 1078597027, "_x_x_x_x_bach_float64_x_x_x_x_", 925070779, 3226817552, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 750442389, 3225062731, "_x_x_x_x_bach_float64_x_x_x_x_", 2034868385, 1078569172, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 1534310935, 1077195361, "_x_x_x_x_bach_float64_x_x_x_x_", 19224522, 1079539054, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 2, "]", "[", "flags", "]", "]", "]" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-66",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 237.0, 2453.0, 191.0, 181.0 ],
									"versionnumber" : 10000,
									"zoom" : 80.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-84",
									"maxclass" : "dada.bodies",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 32.0, 2453.0, 193.0, 184.0 ],
									"showdensity" : 1,
									"versionnumber" : 10000,
									"whole_bodies_data_0000000000" : [ "bodies", "[", "stars", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2429850199, 1078218753, "_x_x_x_x_bach_float64_x_x_x_x_", 1071280312, 1074925114, "]", "[", "density", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1065646817, "]", "[", "radius", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, "]", "[", "notes", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086198784, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072243195, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073291771, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073928572, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074340347, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074752122, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074977148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075183035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]", "[", "planets", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3534188048, 3227004097, "_x_x_x_x_bach_float64_x_x_x_x_", 3531726048, 3225057960, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 2459938865, 1074589706, "_x_x_x_x_bach_float64_x_x_x_x_", 2433002464, 1079320272, "]", "[", "acc", "_x_x_x_x_bach_float64_x_x_x_x_", 3038937322, 1079731710, "_x_x_x_x_bach_float64_x_x_x_x_", 1329544210, 1077503720, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071309127, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070679982, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1068792545, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]" ],
									"whole_bodies_data_count" : [ 1 ],
									"zoom" : 80.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-83",
									"maxclass" : "jit.pwindow",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 15.0, 1543.0, 106.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-81",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 363.0, 1268.0, 230.0, 51.0 ],
									"text" : "Send a \"paintjit\" message followed by a matrix name to send the image onto the matrix only once"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-80",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 261.0, 1282.5, 96.0, 22.0 ],
									"text" : "paintjit othermat"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-78",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 15.0, 1479.0, 24.0, 24.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_mmax" : 1.0,
											"parameter_shortname" : "button[1]",
											"parameter_enum" : [ "off", "on" ],
											"parameter_type" : 2,
											"parameter_longname" : "button[1]"
										}

									}
,
									"varname" : "button[1]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-76",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 15.0, 1512.0, 106.0, 22.0 ],
									"text" : "jit.matrix othermat"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-75",
									"maxclass" : "jit.pwindow",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 15.0, 1377.0, 212.0, 89.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-74",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 15.0, 1273.0, 24.0, 24.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_invisible" : 1,
											"parameter_shortname" : "toggle",
											"parameter_type" : 3,
											"parameter_longname" : "toggle"
										}

									}
,
									"varname" : "toggle"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-72",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 15.0, 1306.0, 71.0, 22.0 ],
									"text" : "qmetro 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-71",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 15.0, 1342.0, 122.0, 22.0 ],
									"text" : "jit.matrix platformmat"
								}

							}
, 							{
								"box" : 								{
									"attr" : "jitmatrix",
									"id" : "obj-70",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 238.0, 1238.0, 198.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"center" : [ -11.328125, -5.0 ],
									"id" : "obj-68",
									"jitmatrix" : "platformmat",
									"maxclass" : "dada.platform",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nnn",
									"outlettype" : [ "", "", "", "bang" ],
									"patching_rect" : [ 238.0, 1321.0, 371.5625, 164.0 ],
									"platform_data_0000000000" : [ "platform", "[", "levelinfo", "[", "title", "Level 1", "]", "[", "hero", "Juan", "]", "[", "bgsprite", "background", "]", "[", "gravity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, "]", "[", "maxtime", "none", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "[", "groundfriction", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "]", "[", "airfriction", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "textcolor", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "intro", 0, "]", "]", "[", "sprites", "[", "[", "name", "background", "]", "[", "pics", "bg.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1084489728, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080745984, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "brick", "]", "[", "pics", "altblock1.png", "altblock2.png", "altblock3.png", "altblock4.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "breakbrick", "]", "[", "pics", "breakbrick.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "ground", "]", "[", "pics", "ground.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "wood", "]", "[", "pics", "wood.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "note", "]", "[", "pics", "note1.png", "note2.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081262080, "]", "]", "[", "[", "name", "questionmark", "]", "[", "pics", "question1.png", "question2.png", "question3.png", "question4.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081262080, "]", "]", "[", "[", "name", "questionidle", "]", "[", "pics", "questionidle.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081262080, "]", "]", "[", "[", "name", "coin", "]", "[", "pics", "coin0.png", "coin1.png", "coin2.png", "coin3.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076363264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081262080, "]", "]", "[", "[", "name", "juanidle", "]", "[", "pics", "juan_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "juanwalk", "]", "[", "pics", "juan_r.png", "juan_walk_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "juanjump", "]", "[", "pics", "juan_jump_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "juandead", "]", "[", "pics", "juan_dead.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanidle", "]", "[", "pics", "superjuan_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanwalk", "]", "[", "pics", "superjuan_r.png", "superjuan_walk_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanjump", "]", "[", "pics", "superjuan_jump_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanswim", "]", "[", "pics", "superjuanswim1.png", "superjuanswim2.png", "superjuanswim3.png", "superjuanswim4.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanfireidle", "]", "[", "pics", "superjuanfire_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanfirewalk", "]", "[", "pics", "superjuanfire_r.png", "superjuanfire_walk_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanfirejump", "]", "[", "pics", "superjuanfire_jump_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanfirefire", "]", "[", "pics", "superjuanfire_fire_r.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "superjuanfirebullet", "]", "[", "pics", "firebullet1.png", "firebullet2.png", "firebullet3.png", "firebullet4.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "plant", "]", "[", "pics", "carnivorousplant1.png", "carnivorousplant2.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077477376, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "duckwalk", "]", "[", "pics", "duck1.png", "duck2.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077608448, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "duckdead", "]", "[", "pics", "duckdead.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077608448, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "evilmushroom", "]", "[", "pics", "evilmushroom1.png", "evilmushroom2.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "evilmushroomdead", "]", "[", "pics", "evilmushroomdead.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "mushroom", "]", "[", "pics", "mushroom.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "star", "]", "[", "pics", "star1.png", "star2.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipetop", "]", "[", "pics", "pipetop.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipemiddle", "]", "[", "pics", "pipemiddle.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipe", "]", "[", "pics", "pipe.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "piperev", "]", "[", "pics", "piperev.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "door", "]", "[", "pics", "door.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "vpmushroom", "]", "[", "pics", "vpmushroom.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipetop", "]", "[", "pics", "pipetop.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipemiddle", "]", "[", "pics", "pipemiddle.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "pipe", "]", "[", "pics", "pipe.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "piperev", "]", "[", "pics", "piperev.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "[", "[", "name", "door", "]", "[", "pics", "door.png", "]", "[", "rect", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "]", "[", "stretch", 1, "]", "[", "slidetime", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, "]", "]", "]", "[", "prototypes", "[", "ground", "block", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "upbumpeable", 0, "]", "[", "downbumpeable", 0, "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "[", "mute", 0, "]", "[", "solo", 0, "]", "[", "lock", 0, "]", "]", "[", "brick", "block", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "upbumpeable", 1, "]", "[", "downbumpeable", 0, "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "[", "mute", 0, "]", "[", "solo", 0, "]", "[", "lock", 0, "]", "]", "[", "wood", "block", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076232192, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Wood", "]", "[", "sprite", "wood", "]", "[", "upbumpeable", 0, "]", "[", "downbumpeable", 0, "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "[", "mute", 0, "]", "[", "solo", 0, "]", "[", "lock", 0, "]", "]", "[", "note", "block", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076363264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Note", "]", "[", "sprite", "note", "]", "[", "upbumpeable", 1, "]", "[", "downbumpeable", 1, "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 45190, 1085536169, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "[", "mute", 0, "]", "[", "solo", 0, "]", "[", "lock", 0, "]", "]", "[", "coin", "coin", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "[", "mute", 0, "]", "[", "solo", 0, "]", "[", "lock", 0, "]", "]", "[", "plant", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072955392, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073217536, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "name", "Plant", "]", "[", "type", 2, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 0, "]", "[", "state", 0, "]", "[", "ability", 128, "]", "[", "howdies", 0, "]", "[", "howkills", 1, "]", "[", "idlesprite", "plant", "]", "[", "walksprite", "none", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "]", "[", "resurrectpositions", "]", "]", "[", "evilmushroom", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", 2, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 1, "]", "[", "ability", 1153, "]", "[", "howdies", 209, "]", "[", "howkills", 14, "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "duck", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078394880, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073217536, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073414144, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "name", "Duck", "]", "[", "type", 2, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 1, "]", "[", "ability", 1153, "]", "[", "howdies", 209, "]", "[", "howkills", 14, "]", "[", "idlesprite", "duck", "]", "[", "walksprite", "duckwalk", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "duckdead", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "duckdead", "]", "[", "deathseq", "[", "dontdie", "]", "[", "give", "hero", 10, "points", "]", "[", "add", "me", "ability", "glide", "]", "[", "add", "me", "ability", "break", "]", "[", "remove", "me", "ability", "walk", "]", "[", "remove", "me", "ability", "die", "during", 200, "]", "[", "change", "me", "[", "sprite", "duckdead", "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 4292955190, 1069128086, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "speed", 8, 0, "]", "[", "state", "gliding", "]", "[", "deathseq", "]", "]", "]", "[", "resurrectpositions", "]", "]", "[", "mushroom", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "Mushroom", "]", "[", "type", 3, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 1, "]", "[", "ability", 1025, "]", "[", "howdies", 15, "]", "[", "howkills", 0, "]", "[", "idlesprite", "mushroom", "]", "[", "walksprite", "mushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "[", "change", "hero", "[", "name", "SuperJuan", "]", "[", "idlesprite", "superjuanidle", "]", "[", "walksprite", "superjuanwalk", "]", "[", "jumpsprite", "superjuanjump", "]", "[", "flysprite", "superjuanswim", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073348608, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 82683, 1071015524, "_x_x_x_x_bach_float64_x_x_x_x_", 82683, 1071015524, "_x_x_x_x_bach_float64_x_x_x_x_", 314021, 1072326246, "_x_x_x_x_bach_float64_x_x_x_x_", 314021, 1072326246, "]", "[", "deathseq", "[", "dontdie", "]", "[", "remove", "hero", "ability", "die", "during", 2000, "]", "[", "change", "hero", "[", "name", "Juan", "]", "[", "idlesprite", "juanidle", "]", "[", "walksprite", "juanwalk", "]", "[", "jumpsprite", "juanjump", "]", "[", "height", 1, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 4294421938, 1071225239, "_x_x_x_x_bach_float64_x_x_x_x_", 4294421938, 1071225239, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "deathseq", "]", "]", "[", "remove", "hero", "ability", "break", "]", "]", "]", "[", "add", "hero", "ability", "break", "]", "]", "[", "resurrectpositions", "]", "]", "[", "vpmushroom", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "VPMushroom", "]", "[", "type", 3, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 1, "]", "[", "ability", 1025, "]", "[", "howdies", 15, "]", "[", "howkills", 0, "]", "[", "idlesprite", "vpmushroom", "]", "[", "walksprite", "vpmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "[", "give", "hero", 1, "vp", "]", "]", "[", "resurrectpositions", "]", "]", "[", "star", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "Star", "]", "[", "type", 3, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 2, "]", "[", "ability", 1026, "]", "[", "howdies", 15, "]", "[", "howkills", 0, "]", "[", "idlesprite", "star", "]", "[", "walksprite", "star", "]", "[", "jumpsprite", "star", "]", "[", "glidesprite", "star", "]", "[", "flysprite", "star", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "[", "remove", "hero", "ability", "die", "during", 15000, "]", "]", "[", "resurrectpositions", "]", "]", "[", "firebullet", "gamechar", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071906816, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071906816, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070858240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070858240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070858240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070858240, "]", "[", "name", "FireBullet", "]", "[", "type", 4, "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", 4, "]", "[", "ability", 1156, "]", "[", "howdies", 32, "]", "[", "howkills", 15, "]", "[", "idlesprite", "superjuanfirebullet", "]", "[", "walksprite", "none", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "superjuanfirebullet", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "]", "[", "resurrectpositions", "]", "]", "[", "pipe", "portal", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "name", "Pipe", "]", "[", "sprite", "pipe", "]", "[", "open", 1, "]", "[", "howenter", 1, "]", "[", "howexit", 0, "]", "[", "enterseq", "[", "goto", "level", "juanlevelswim.txt", "at", "PipeRev", "]", "]", "[", "exitseq", "]", "[", "music", "]", "[", "heroonly", 1, "]", "]", "[", "door", "portal", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "name", "Door", "]", "[", "sprite", "door", "]", "[", "open", 1, "]", "[", "howenter", 4, "]", "[", "howexit", 0, "]", "[", "enterseq", "[", "win", "]", "]", "[", "exitseq", "]", "[", "music", "]", "[", "heroonly", 1, "]", "]", "]", "[", "gamechars", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 858993459, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 858993459, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "Juan", "]", "[", "type", "usercontrol", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 3, "]", "[", "direction", 0, "]", "[", "state", "idle", "]", "[", "ability", "walk", "jump", "kill", "die", "]", "[", "howdies", "left", "right", "top", "bottom", "bullet", "glide", "]", "[", "howkills", "bottom", "]", "[", "idlesprite", "juanidle", "]", "[", "walksprite", "juanwalk", "]", "[", "jumpsprite", "juanjump", "]", "[", "glidesprite", "juanidle", "]", "[", "flysprite", "juanfly", "]", "[", "deadsprite", "juandead", "]", "[", "deathseq", "die", "]", "[", "resurrectpositions", "[", 2, 1, "]", "[", 17, 1, "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072955392, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073217536, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "name", "Plant", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 0, "]", "[", "state", "idle", "]", "[", "ability", "kill", "]", "[", "howdies", "none", "]", "[", "howkills", "top", "]", "[", "idlesprite", "plant", "]", "[", "walksprite", "none", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078132736, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072955392, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073217536, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "name", "Plant", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 0, "]", "[", "state", "idle", "]", "[", "ability", "kill", "]", "[", "howdies", "none", "]", "[", "howkills", "top", "]", "[", "idlesprite", "plant", "]", "[", "walksprite", "none", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078165504, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072955392, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073217536, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "name", "Plant", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 0, "]", "[", "state", "idle", "]", "[", "ability", "kill", "]", "[", "howdies", "none", "]", "[", "howkills", "top", "]", "[", "idlesprite", "plant", "]", "[", "walksprite", "none", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "none", "]", "[", "deathseq", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3435973837, 1077185740, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", -1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 29137058, 1078404710, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073053696, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073414144, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "name", "Duck", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", -1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "duck", "]", "[", "walksprite", "duckwalk", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "duckdead", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "duckdead", "]", "[", "deathseq", "[", "dontdie", "]", "[", "give", "hero", 10, "points", "]", "[", "add", "me", "ability", "glide", "]", "[", "add", "me", "ability", "break", "]", "[", "remove", "me", "ability", "walk", "]", "[", "remove", "me", "ability", "die", "during", 200, "]", "[", "change", "me", "[", "sprite", "duckdead", "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1069128089, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "speed", 8, 0, "]", "[", "state", "gliding", "]", "[", "deathseq", "]", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 29137058, 1078470246, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073053696, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073414144, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "name", "Duck", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "duck", "]", "[", "walksprite", "duckwalk", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "duckdead", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "duckdead", "]", "[", "deathseq", "[", "dontdie", "]", "[", "give", "hero", 10, "points", "]", "[", "add", "me", "ability", "glide", "]", "[", "add", "me", "ability", "break", "]", "[", "remove", "me", "ability", "walk", "]", "[", "remove", "me", "ability", "die", "during", 200, "]", "[", "change", "me", "[", "sprite", "duckdead", "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1069128089, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072365568, "]", "[", "speed", 8, 0, "]", "[", "state", "gliding", "]", "[", "deathseq", "]", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078722560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom" ],
									"platform_data_0000000001" : [ "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 29137058, 1078830694, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078886400, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1076107673, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", -1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079246848, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079230464, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079197696, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079164928, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "ext", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "name", "EvilMushroom", "]", "[", "type", "enemy", "]", "[", "points", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "vp", 1, "]", "[", "direction", 1, "]", "[", "state", "walking", "]", "[", "ability", "walk", "kill", "die", "]", "[", "howdies", "top", "bump", "bullet", "glide", "]", "[", "howkills", "left", "right", "bottom", "]", "[", "idlesprite", "evilmushroom", "]", "[", "walksprite", "evilmushroom", "]", "[", "jumpsprite", "none", "]", "[", "glidesprite", "none", "]", "[", "flysprite", "none", "]", "[", "deadsprite", "evilmushroomdead", "]", "[", "deathseq", "[", "give", "hero", 10, "points", "]", "]", "[", "resurrectpositions", "]", "]", "]", "[", "blocks", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074266112, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076232192, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076232192, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Wood", "]", "[", "sprite", "wood", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076363264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076363264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Note", "]", "[", "sprite", "note", "]", "[", "solid", 1, "]", "[", "howhit", "left", "right", "top", "bottom", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085536168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076494336, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076494336, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Wood", "]", "[", "sprite", "wood", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076625408, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076625408, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076953088, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077084160, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077215232, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077215232, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077280768, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077280768, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "MushroomQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "[", "generate", "mushroom", "from", "me", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 824634, 1085089909, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077346304, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077346304, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077411840, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077477376, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077542912, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077608448, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077608448, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077870592, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077936128, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077968896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077968896, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "CoinsStarQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086348310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078001664, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078034432, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1 ],
									"platform_data_0000000002" : [ "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078067200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078067200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078067200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078067200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074266112, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078099968, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078132736, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078165504, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078198272, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078231040, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078263808, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078296576, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078329344, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078362112, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078394880, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078394880, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078427648, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078427648, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078460416, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078460416, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "CoinsStarQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "[", "generate", "star", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086348310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078493184, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078493184, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078525952, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078558720, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078591488, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078624256, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078657024, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078722560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078722560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078755328, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Wood", "]", "[", "sprite", "wood", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078755328, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078755328, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078755328, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078788096, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Wood", "]", "[", "sprite", "wood", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078788096, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078788096, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078820864, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078820864, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Note", "]", "[", "sprite", "note", "]", "[", "solid", 1, "]", "[", "howhit", "left", "right", "top", "bottom", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085536168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078820864, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "CoinsStarQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "[", "generate", "mushroom", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086348310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078886400, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078886400, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078886400, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078919168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078919168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078919168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078951936, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079001088, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079017472, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "CoinsStarQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "[", "generate", "vpmushroom", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086348310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079017472, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079033856, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079050240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079066624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "CoinsStarQuestionMark", "]", "[", "sprite", "questionmark", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "give", "hero", 10, "points", "]", "[", "[", "generate", "star", "]", "[", "change", "me", "[", "sprite", "questionidle", "]", "[", "howhit", "]", "]", "]", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "[", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086348310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082081280, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079099392, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079099392, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite" ],
									"platform_data_0000000003" : [ "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079115776, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079115776, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079132160, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079132160, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074790400, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Brick", "]", "[", "sprite", "brick", "]", "[", "solid", 1, "]", "[", "howhit", "bottom", "glide", "]", "[", "hitseq", "break", "]", "[", "loophitseq", 1, "]", "[", "breaksprite", "breakbrick", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079148544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079164928, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079181312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079197696, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079214080, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079230464, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079246848, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079263232, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079279616, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079296000, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079312384, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079328768, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079345152, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079361536, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079377920, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079394304, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079410688, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079427072, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079443456, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079459840, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079476224, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079492608, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079508992, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079525376, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079541760, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079558144, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079590912, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079607296, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Ground", "]", "[", "sprite", "ground", "]", "[", "solid", 1, "]", "[", "howhit", "none", "]", "[", "hitseq", "]", "[", "loophitseq", 0, "]", "[", "breaksprite", "none", "]", "[", "state", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "music", "]", "]", "]", "[", "coins", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075052544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075314688, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076887552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076953088, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079115776, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079132160, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079148544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079164928, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079181312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079197696, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079312384, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079328768, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079345152, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079361536, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079377920, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079394304, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075838976, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079410688, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075576832, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072168960, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "name", "Coin", "]", "[", "sprite", "coin", "]", "[", "takeable", 1, "]", "[", "taken", 0, "]", "[", "pointsgiven", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, "]", "[", "vpgiven", 0, "]", "[", "music", "roll", "[", "[", 0, "[", 7900, 100, 100, "]", "]", "[", 100, "[", 8400, 100, 100, "]", "]", "]", "]", "]", "]", "[", "portals", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079377920, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "name", "Pipe", "]", "[", "sprite", "pipe", "]", "[", "open", 1, "]", "[", "howenter", "top", "]", "[", "howexit", "none", "]", "[", "enterseq", "[", "goto", "portal", "PipeFromAbove", "]", "]", "[", "exitseq", "]", "[", "music", "]", "[", "heroonly", 1, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079476224, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075970048, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "name", "PipeFromAbove", "]", "[", "sprite", "piperev", "]", "[", "open", 1, "]", "[", "howenter", "none", "]", "[", "howexit", "bottom", "]", "[", "enterseq", "]", "[", "exitseq", "]", "[", "music", "]", "[", "heroonly", 1, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079525376, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073741824, "]", "[", "name", "Pipe", "]", "[", "sprite", "pipe", "]", "[", "open", 1, "]", "[", "howenter", "top", "]", "[", "howexit", "none", "]", "[", "enterseq", "[", "add", "hero", "ability", "fly", "]", "[", "goto", "level", "juanlevelswim.txt", "at", "PipeRev", "with", "[", "keephero", 1, "]", "]", "]", "[", "exitseq", "]", "[", "music", "]", "[", "heroonly", 1, "]", "]", "]" ],
									"platform_data_count" : [ 4 ],
									"versionnumber" : 10000,
									"zoom" : 102.499999999999986
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 2174.0, 588.0, 20.0 ],
									"text" : "Use swipe to move left/right/up/down; use pinch to zoom; use tap to play/stop.",
									"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-31",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 1813.0, 588.0, 33.0 ],
									"text" : "Unfortunately dada objects cannot natively support Mira. You can however mirror them using image export, fpic, and mira.multitouch. Notice that the \"notifypaint\" sends a bang whenever the object display is refreshed.",
									"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubblepoint" : 0.21,
									"bubbleside" : 3,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-34",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 32.0, 2088.5, 130.0, 54.0 ],
									"text" : "We keep in sync whenever the object is painted"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-35",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 165.0, 2109.5, 24.0, 24.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_mmax" : 1.0,
											"parameter_shortname" : "button",
											"parameter_enum" : [ "off", "on" ],
											"parameter_type" : 2,
											"parameter_longname" : "button"
										}

									}
,
									"varname" : "button"
								}

							}
, 							{
								"box" : 								{
									"attr" : "notifypaint",
									"id" : "obj-36",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 55.0, 1887.5, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubblepoint" : 0.21,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-37",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 413.0, 2117.5, 190.0, 54.0 ],
									"text" : "Any message coming from mira.multitouch is routed to bach.score with \"mt\""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 336.324158000000011, 2117.5, 71.0, 22.0 ],
									"text" : "prepend mt"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.75, 0.75, 0.75, 0.2 ],
									"id" : "obj-39",
									"maxclass" : "mira.multitouch",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 336.324158000000011, 1950.5, 247.0, 156.0 ],
									"pinch_enabled" : 1,
									"rotate_enabled" : 0,
									"swipe_enabled" : 1,
									"swipe_touch_count" : 0,
									"tap_enabled" : 1,
									"tap_tap_count" : 0,
									"tap_touch_count" : 0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-40",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 165.0, 2137.5, 135.0, 22.0 ],
									"text" : "speedlim 100 @defer 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-41",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 336.324158000000011, 1900.5, 144.0, 22.0 ],
									"text" : "pic /tmp/mydadastuff.png"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 336.324158000000011, 1873.5, 56.0, 22.0 ],
									"text" : "deferlow"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 165.0, 2084.5, 107.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.keys painted"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-46",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 32.0, 1859.5, 195.0, 22.0 ],
									"text" : "exportimage /tmp/mydadastuff.png"
								}

							}
, 							{
								"box" : 								{
									"autofit" : 1,
									"id" : "obj-49",
									"maxclass" : "fpic",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "jit_matrix" ],
									"patching_rect" : [ 336.324158000000011, 1950.5, 247.0, 156.0 ],
									"pic" : "/tmp/mydadastuff.png"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "[", "room", "[", "vertices", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1287770821, 3226908280, "_x_x_x_x_bach_float64_x_x_x_x_", 3651081886, 3227133123, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3007196477, 1079724423, "_x_x_x_x_bach_float64_x_x_x_x_", 3651081886, 3227133123, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3007196477, 1079724423, "_x_x_x_x_bach_float64_x_x_x_x_", 643885410, 1079499580, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1287770821, 3226908280, "_x_x_x_x_bach_float64_x_x_x_x_", 643885410, 1079499580, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3467215638, 1079903564, "_x_x_x_x_bach_float64_x_x_x_x_", 1539269738, 3226786000, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1632944522, 1080567190, "_x_x_x_x_bach_float64_x_x_x_x_", 67746144, 1074841951, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1990820630, 1079666118, "_x_x_x_x_bach_float64_x_x_x_x_", 3829439382, 1079202421, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 89327152, 1077952461, "_x_x_x_x_bach_float64_x_x_x_x_", 1039868752, 3223623555, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "[", "edges", "[", 1, 2, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 2, 3, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 3, 4, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 4, 1, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 5, 6, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 6, 7, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 7, 8, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 8, 5, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "]", "[", "balls", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]" ],
									"bounce_data_count" : [ 1 ],
									"center" : [ -35.325836258179443, 3.174145056319566 ],
									"id" : "obj-52",
									"maxclass" : "dada.bounce",
									"notifypaint" : 1,
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 32.0, 1917.5, 248.0, 152.0 ],
									"versionnumber" : 10000,
									"zoom" : 66.054666928924064
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 426.0, 786.0, 163.0, 21.0 ],
									"text" : "coord * (zoom/100) = pixel",
									"textcolor" : [ 0.50196099281311, 0.50196099281311, 0.50196099281311, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-7",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 442.0, 733.0, 138.0, 51.0 ],
									"text" : "Choose height and width in pixel; choose zoom"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-30",
									"linecount" : 3,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 248.0, 733.0, 174.0, 49.0 ],
									"text" : "exportimage /tmp/foo.png @pixelwidth 3000 @pixelheight 2000 @zoom 10"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 42.0, 660.0, 161.0, 22.0 ],
									"text" : "exportimage /tmp/mypic.png"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-28",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 426.0, 689.5, 191.0, 37.0 ],
									"text" : "Shift the center, choose width and height (in coordinates) "
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-21",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 346.0, 512.0, 343.0, 22.0 ],
									"text" : "exportimage /tmp/foo.png @center -41.328125 -5. @height 10"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-65",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 15.0, 1208.0, 588.0, 20.0 ],
									"text" : "Set the \"jitmatrix\" attribute to automatically mirror an object onto a jitter matrix",
									"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-51",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 211.0, 658.0, 136.0, 24.0 ],
									"text" : "Same, with filename"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-50",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 101.0, 619.0, 186.0, 37.0 ],
									"text" : "Save object as a PNG image (dialog appears)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "dada.multibrot",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 231.0, 811.0, 197.0, 145.0 ],
									"versionnumber" : 10000
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-45",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 18.0, 619.0, 77.0, 22.0 ],
									"text" : "exportimage"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-47",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 231.0, 689.5, 186.0, 35.0 ],
									"text" : "exportimage /tmp/foo.png @center 1 0 @width 3 @height 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-48",
									"maxclass" : "dada.bodies",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 18.0, 718.0, 193.0, 184.0 ],
									"showdensity" : 1,
									"versionnumber" : 10000,
									"whole_bodies_data_0000000000" : [ "bodies", "[", "stars", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2429850199, 1078218753, "_x_x_x_x_bach_float64_x_x_x_x_", 1071280312, 1074925114, "]", "[", "density", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1065646817, "]", "[", "radius", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, "]", "[", "notes", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086198784, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072243195, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073291771, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073928572, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074340347, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074752122, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074977148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075183035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3730234194, 3225411580, "_x_x_x_x_bach_float64_x_x_x_x_", 3087315433, 3225574968, "]", "[", "density", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1065646817, "]", "[", "radius", "_x_x_x_x_bach_float64_x_x_x_x_", 1979773970, 1079000763, "]", "[", "notes", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086198784, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072243195, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073291771, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073928572, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074340347, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074752122, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074977148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075183035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 2405181686, 1071707586, "_x_x_x_x_bach_float64_x_x_x_x_", 3951369912, 1067366481, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]", "[", "planets", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222454130, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078825331, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080594642, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076930304, "]", "[", "acc", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222444273, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3229855558, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071309127, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070679982, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1068792545, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]" ],
									"whole_bodies_data_count" : [ 1 ],
									"zoom" : 80.0
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-27",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 508.181030000000021, 4.0, 102.0, 64.0 ],
									"text" : "Most objects respond to an \"autozoom\" command"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 437.0, 25.0, 63.0, 22.0 ],
									"text" : "autozoom"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-23",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 377.5, 51.5, 102.0, 37.0 ],
									"text" : "Coordinates of the center"
								}

							}
, 							{
								"box" : 								{
									"attr" : "center",
									"id" : "obj-24",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 186.5, 59.0, 189.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 346.0, 422.5, 241.0, 22.0 ],
									"text" : "dada.base dadacommondbhelp winterdb.txt"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-19",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 544.681029999999964, 360.0, 63.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 297.0, 360.0, 63.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 135.0, 356.5, 158.0, 37.0 ],
									"text" : "Every object has its own notification outlet"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-13",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 472.021575999999982, 78.0, 153.0, 52.0 ],
									"text" : "Some objects have independent vertical zoom"
								}

							}
, 							{
								"box" : 								{
									"attr" : "vzoom",
									"id" : "obj-12",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 464.0, 133.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"center" : [ -712.745347807499911, -5345.375 ],
									"colorfield" : "tonalcentroid5th",
									"convexcombmax" : [ 1.0 ],
									"convexcombmin" : [ 0.0 ],
									"database" : "dadacommondbhelp",
									"id" : "obj-10",
									"maxclass" : "dada.cartesian",
									"mode" : 0,
									"numinlets" : 1,
									"numoutlets" : 4,
									"out" : "nnn",
									"outlettype" : [ "", "", "", "bang" ],
									"patching_rect" : [ 422.0, 167.0, 203.02157600000001, 184.0 ],
									"query" : "SELECT * FROM scores",
									"shapefield" : "filename",
									"sizefield" : "loudness",
									"table" : "scores",
									"versionnumber" : 10000,
									"vzoom" : 0.902126616412331,
									"xfield" : "spread",
									"yfield" : "centroid",
									"zoom" : 2.577164317867063
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-6",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 347.0, 112.0, 102.0, 24.0 ],
									"text" : "Change zoom"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 61.5, 364.0, 63.0, 22.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print"
								}

							}
, 							{
								"box" : 								{
									"attr" : "zoom",
									"id" : "obj-8",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 193.0, 113.0, 150.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "[", "room", "[", "vertices", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 393870936, 3225768614, "_x_x_x_x_bach_float64_x_x_x_x_", 816601484, 3226604335, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1780115129, 3225802520, "_x_x_x_x_bach_float64_x_x_x_x_", 2499577158, 1078522673, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2769923502, 1077367865, "_x_x_x_x_bach_float64_x_x_x_x_", 3507199166, 1078096279, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2769923502, 1077367865, "_x_x_x_x_bach_float64_x_x_x_x_", 237488823, 1079541046, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2839323296, 3226576867, "_x_x_x_x_bach_float64_x_x_x_x_", 237488823, 1079541046, "]", "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "[", "edges", "[", 1, 2, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 2, 3, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 3, 4, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 4, 1, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 5, 6, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 6, 7, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 7, 8, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 2062535806, 1086250484, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "[", 8, 5, "[", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, "]", "[", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "]", "]", "]", "]", "[", "balls", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3150967488, 3223229744, "_x_x_x_x_bach_float64_x_x_x_x_", 3478365811, 1079045328, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226776511, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078724536, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 2576980378, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 2, "]", "[", "flags", "]", "]", "]" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-5",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 223.0, 167.0, 191.0, 181.0 ],
									"versionnumber" : 10000,
									"zoom" : 80.0
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-4",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 18.0, -93.0, 30.0, 30.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 18.0, -55.5, 69.0, 22.0 ],
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
									"text" : "thispatcher"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 240.0, 10.0, 120.0, 37.0 ],
									"text" : "Set/get domain/range"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 135.0, 10.0, 99.0, 22.0 ],
									"text" : "range -200 200"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 18.0, 10.0, 108.0, 22.0 ],
									"text" : "domain -180 180"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 122.5, 41.0, 62.0, 22.0 ],
									"text" : "getrange"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 36.5, 41.0, 71.0, 22.0 ],
									"text" : "getdomain"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "dada.bodies",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 18.0, 167.0, 193.0, 184.0 ],
									"showdensity" : 1,
									"versionnumber" : 10000,
									"whole_bodies_data_0000000000" : [ "bodies", "[", "stars", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2429850199, 1078218753, "_x_x_x_x_bach_float64_x_x_x_x_", 1071280312, 1074925114, "]", "[", "density", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1065646817, "]", "[", "radius", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, "]", "[", "notes", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086198784, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072243195, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073291771, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073928572, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074340347, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074752122, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086408960, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074977148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086364160, "]", "[", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075183035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086325760, "]", "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]", "[", "planets", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222454130, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078825331, "]", "[", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080594642, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076930304, "]", "[", "acc", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222444273, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3229855558, "]", "[", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071309127, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070679982, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1068792545, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "]", "[", "channel", 1, "]", "[", "flags", "]", "]", "]" ],
									"whole_bodies_data_count" : [ 1 ],
									"zoom" : 80.0
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"id" : "obj-67",
									"ignoreclick" : 1,
									"maxclass" : "mira.frame",
									"numinlets" : 0,
									"numoutlets" : 0,
									"patching_rect" : [ 326.197784423828125, 1924.5, 267.252753973007202, 190.0 ],
									"tabname" : "dada on tablet"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"source" : [ "obj-10", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-101", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"order" : 2,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"order" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"order" : 1,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"order" : 2,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"order" : 0,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"order" : 1,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"order" : 2,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"order" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"order" : 1,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"source" : [ "obj-35", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"midpoints" : [ 345.824158000000011, 2151.5, 318.0, 2151.5, 318.0, 1883.5, 41.5, 1883.5 ],
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-43", 0 ],
									"midpoints" : [ 174.5, 2164.5, 308.662079000000006, 2164.5, 308.662079000000006, 1867.5, 345.824158000000011, 1867.5 ],
									"order" : 0,
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"midpoints" : [ 174.5, 2164.5, 28.0, 2164.5, 28.0, 1854.5, 41.5, 1854.5 ],
									"order" : 1,
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-49", 0 ],
									"source" : [ "obj-41", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-41", 0 ],
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-35", 0 ],
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"source" : [ "obj-5", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"source" : [ "obj-52", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-57", 0 ],
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"source" : [ "obj-56", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-56", 0 ],
									"order" : 1,
									"source" : [ "obj-57", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-59", 0 ],
									"order" : 0,
									"source" : [ "obj-57", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-93", 0 ],
									"source" : [ "obj-61", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-63", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-90", 1 ],
									"source" : [ "obj-66", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-69", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-68", 0 ],
									"source" : [ "obj-70", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-75", 0 ],
									"source" : [ "obj-71", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-71", 0 ],
									"source" : [ "obj-72", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-72", 0 ],
									"source" : [ "obj-74", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-83", 0 ],
									"source" : [ "obj-76", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-77", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-76", 0 ],
									"source" : [ "obj-78", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"order" : 2,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"order" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"order" : 1,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-68", 0 ],
									"order" : 0,
									"source" : [ "obj-80", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-78", 0 ],
									"midpoints" : [ 270.5, 1471.25, 24.5, 1471.25 ],
									"order" : 1,
									"source" : [ "obj-80", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-82", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 1 ],
									"source" : [ "obj-84", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-61", 0 ],
									"order" : 1,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-66", 0 ],
									"order" : 3,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-84", 0 ],
									"order" : 4,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"order" : 5,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-90", 0 ],
									"midpoints" : [ 24.5, 2649.5, 246.5, 2649.5 ],
									"order" : 2,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-91", 0 ],
									"midpoints" : [ 24.5, 2642.5, 445.5, 2642.5 ],
									"order" : 0,
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-87", 0 ],
									"source" : [ "obj-89", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-88", 0 ],
									"source" : [ "obj-90", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-92", 0 ],
									"source" : [ "obj-91", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-97", 0 ],
									"source" : [ "obj-93", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-94", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-96", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-91", 1 ],
									"source" : [ "obj-97", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 99.567627000000002, 649.0, 398.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"border" : 0,
					"filename" : "helpname.js",
					"id" : "obj-2",
					"ignoreclick" : 1,
					"jsarguments" : [ "dada" ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 10.0, 106.472000122070312, 57.599853515625 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"hidden" : 1,
					"source" : [ "obj-9", 0 ]
				}

			}
 ]
	}

}
