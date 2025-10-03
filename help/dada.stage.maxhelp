{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 9,
			"minor" : 0,
			"revision" : 7,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 100.0, 100.0, 809.0, 633.0 ],
		"gridsize" : [ 5.0, 5.0 ],
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 809.0, 607.0 ],
						"default_fontsize" : 13.0,
						"gridsize" : [ 5.0, 5.0 ],
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bgmode" : 0,
									"border" : 0,
									"clickthrough" : 0,
									"enablehscroll" : 0,
									"enablevscroll" : 0,
									"id" : "obj-7",
									"lockeddragscroll" : 0,
									"lockedsize" : 0,
									"maxclass" : "bpatcher",
									"name" : "dada.commons.maxpat",
									"numinlets" : 0,
									"numoutlets" : 0,
									"offset" : [ 0.0, 0.0 ],
									"patching_rect" : [ 2.0, 4.0, 673.0, 516.0 ],
									"viewvisibility" : 1
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 72.0, 224.0, 73.0, 22.0 ],
					"saved_object_attributes" : 					{
						"fontsize" : 13.0
					}
,
					"text" : "p commons",
					"varname" : "basic_tab[8]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 809.0, 607.0 ],
						"default_fontsize" : 13.0,
						"gridsize" : [ 5.0, 5.0 ],
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 271.0, 504.0, 94.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print Res"
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
									"patching_rect" : [ 241.0, 90.567627000000002, 113.0, 40.0 ],
									"text" : "Set or get domain/range"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 134.0, 83.567627000000002, 99.0, 23.0 ],
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
									"patching_rect" : [ 17.0, 83.567627000000002, 108.0, 23.0 ],
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
									"patching_rect" : [ 103.0, 111.567627000000002, 62.0, 23.0 ],
									"text" : "getrange"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 111.567627000000002, 71.0, 23.0 ],
									"text" : "getdomain"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.901796, 0.956763, 0.776819, 1.0 ],
									"cardbordercolor" : [ 0.501961, 0.501961, 0.501961, 0.43 ],
									"center" : [ 12.722308, -109.372269000000003 ],
									"gridcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"hint" : "Ctrl+Click & Drag on the icons to change their gain",
									"id" : "obj-1",
									"maxclass" : "dada.stage",
									"maximum" : 12.0,
									"minimum" : -90.0,
									"numdigits" : 0,
									"numinlets" : 2,
									"numoutlets" : 3,
									"out" : "nn",
									"outlettype" : [ "", "", "bang" ],
									"patching_rect" : [ 17.0, 159.75, 527.0, 325.5 ],
									"presentation" : 1,
									"presentation_rect" : [ 271.0, 77.0, 613.0, 335.0 ],
									"showgrid" : 1,
									"slope" : 0.5,
									"stage_data_0000000000" : [ "stage", "[", "cards", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225419776, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079853056, "]", "[", "name", "2Fl", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Fl.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077215232, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079869440, "]", "[", "name", "2Ob", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Ob.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225485312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080459264, "]", "[", "name", "2ClBb", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Cl.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080451072, "]", "[", "name", "2Bn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Bn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227402240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080926208, "]", "[", "name", "2Hn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Hn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223977984, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080934400, "]", "[", "name", "2TpC", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Tp.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227787264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223453696, "]", "[", "name", "2Vn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Vn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3221225472, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078460416, "]", "[", "name", "1Va", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Va.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080049664, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "name", "1Vc", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Vc.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080492032, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223977984, "]", "[", "name", "1Cb", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Cb.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "]" ],
									"stage_data_count" : [ 1 ],
									"versionnumber" : 40000
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.stage" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 229.568008422851562, 57.599853515625 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-11", 0 ]
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
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "GreenTextButtons",
								"parentstyle" : "RedTextButtons",
								"multi" : 0
							}
, 							{
								"name" : "RedTextButtons",
								"default" : 								{
									"accentcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
									"bgcolor" : [ 0.827321, 0.874747, 0.7195, 1.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"elementcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontname" : [ "Helvetica" ],
									"selectioncolor" : [ 0.1, 0.1, 0.1, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 15.0, 119.0, 106.0, 22.0 ],
					"saved_object_attributes" : 					{
						"fontsize" : 13.0
					}
,
					"text" : "p \"domain, range\"",
					"varname" : "basic_tab[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 809.0, 607.0 ],
						"default_fontsize" : 13.0,
						"gridsize" : [ 5.0, 5.0 ],
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-14",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 303.0, 250.25, 145.0, 40.0 ],
									"text" : "Relocate all icons in the specified folder"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 115.0, 258.75, 182.0, 23.0 ],
									"text" : "relocate /My/Cool/New/Folder"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-3",
									"linecount" : 7,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 456.0, 487.0, 325.0, 108.0 ],
									"text" : "Basic interface: \nScroll the mouse to move the region\nCmd+Scroll (mac) or Ctrl+Scroll (win) to change zoom\nEsc to re-center\n\nCmd+Z (mac) or Ctrl+Z (win) to undo\nCmd+Shift+Z (mac) or Ctrl+Y (win) to redo",
									"textcolor" : [ 1.0, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-6",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 640.0, 232.5, 151.0, 40.0 ],
									"text" : "Allow card deletion from interface"
								}

							}
, 							{
								"box" : 								{
									"attr" : "allowdeletion",
									"id" : "obj-5",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 476.0, 241.0, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 139.0, 223.0, 117.0, 25.0 ],
									"text" : "Delete all cards"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 93.0, 223.0, 39.0, 23.0 ],
									"text" : "clear"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 3,
									"id" : "obj-35",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 229.0, 562.5, 146.0, 40.0 ],
									"text" : "bang when changed from interface"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 378.0, 571.0, 24.0, 24.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-31",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 625.0, 439.25, 163.0, 40.0 ],
									"text" : "Number of displayed digits in the card value"
								}

							}
, 							{
								"box" : 								{
									"attr" : "numdigits",
									"id" : "obj-30",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 461.0, 447.75, 150.0, 23.0 ]
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
									"patching_rect" : [ 625.0, 395.25, 151.0, 40.0 ],
									"text" : "Fader slope (-1 to 1, 0 = linear)"
								}

							}
, 							{
								"box" : 								{
									"attr" : "slope",
									"id" : "obj-27",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 461.0, 403.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-25",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 625.0, 336.75, 151.0, 40.0 ],
									"text" : "Maximum and minimum card value"
								}

							}
, 							{
								"box" : 								{
									"attr" : "minimum",
									"id" : "obj-24",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 461.0, 363.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "maximum",
									"id" : "obj-22",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 461.0, 331.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 108.0, 571.0, 104.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print hover"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-19",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 645.0, 269.75, 151.0, 54.0 ],
									"text" : "Send mousehover information from middle outlet"
								}

							}
, 							{
								"box" : 								{
									"attr" : "hoverinfo",
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 476.0, 283.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 229.0, 184.0, 236.0, 25.0 ],
									"text" : "Delete one or more cards (by name)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 72.0, 185.0, 149.0, 23.0 ],
									"text" : "deletecards Foo Foobar"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-13",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 590.0, 114.5, 117.0, 25.0 ],
									"text" : "...or more cards"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 36.0, 108.0, 550.0, 38.0 ],
									"text" : "addcards [[coord -100 40] [name Bar] [icon hexacube.png] [value 0.1] [height 60] [width -1]] [[coord 100 -40] [name Foobar] [icon hexacube.png] [value 0.9] [height 60] [width -1]]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 148.0, 539.0, 21.0 ],
									"text" : "If you leave height or width as negative, it'll be inferred from icon proportions.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 520.0, 74.0, 87.0, 25.0 ],
									"text" : "Add one..."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.0, 75.0, 492.0, 23.0 ],
									"text" : "addcards [[coord 0 0] [name Foo] [icon cube.png] [value 0.5] [height 60] [width -1]]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "dada.stage",
									"numinlets" : 2,
									"numoutlets" : 3,
									"out" : "nn",
									"outlettype" : [ "", "", "bang" ],
									"patching_rect" : [ 14.0, 326.75, 381.0, 222.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 271.0, 77.0, 300.0, 300.0 ],
									"stage_data_0000000000" : [ "stage", "[", "cards", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "name", "Foo", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, "]", "[", "icon", "cube.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227090944, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078099968, "]", "[", "name", "Bar", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1069128089, "]", "[", "icon", "hexacube.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225681920, "]", "[", "name", "Foobar", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 52429, 1072483532, "]", "[", "icon", "hexacube.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078853632, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "]" ],
									"stage_data_count" : [ 1 ],
									"versionnumber" : 40000
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.stage" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 229.568008422851562, 57.599853515625 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-1", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-12", 0 ]
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
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "GreenTextButtons",
								"parentstyle" : "RedTextButtons",
								"multi" : 0
							}
, 							{
								"name" : "RedTextButtons",
								"default" : 								{
									"accentcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
									"bgcolor" : [ 0.827321, 0.874747, 0.7195, 1.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"elementcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontname" : [ "Helvetica" ],
									"selectioncolor" : [ 0.1, 0.1, 0.1, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 31.0, 160.0, 48.0, 22.0 ],
					"saved_object_attributes" : 					{
						"fontsize" : 13.0
					}
,
					"text" : "p more",
					"varname" : "basic_tab[2]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 300.0, 205.0, 153.0, 22.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter.js",
						"parameter_enable" : 0
					}
,
					"text" : "js helpstarter.js dada.stage"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 100.0, 126.0, 809.0, 607.0 ],
						"default_fontsize" : 13.0,
						"gridsize" : [ 5.0, 5.0 ],
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 0,
									"id" : "obj-36",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 326.0, 505.0, 222.0, 40.0 ],
									"text" : "Use the mouse to move the cards",
									"textcolor" : [ 1.0, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 0,
									"id" : "obj-37",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 326.0, 532.0, 317.0, 40.0 ],
									"text" : "Cmd+click (mac) or Ctrl+click (win) to delete cards",
									"textcolor" : [ 1.0, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 0,
									"id" : "obj-38",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 326.0, 558.5, 379.0, 40.0 ],
									"text" : "Ctrl+click (mac) or Shift+Ctrl+click (win) to change their value",
									"textcolor" : [ 1.0, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 64.0, 153.0, 119.0, 25.0 ],
									"text" : "Outputs all data"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 16.0, 538.0, 112.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"text" : "bach.print AllData"
								}

							}
, 							{
								"box" : 								{
									"attr" : "cardbordercolor",
									"id" : "obj-31",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 495.25, 180.0, 23.0 ],
									"text_width" : 119.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-29",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 560.0, 443.0, 150.0, 21.0 ],
									"text" : "Card contour:"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 555.0, 168.0, 160.0, 21.0 ],
									"text" : "Show/hide card elements:"
								}

							}
, 							{
								"box" : 								{
									"attr" : "showtext",
									"id" : "obj-26",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 267.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "showicons",
									"id" : "obj-24",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 242.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "showfaders",
									"id" : "obj-22",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 217.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "showvalue",
									"id" : "obj-20",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 192.75, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 555.0, 306.0, 150.0, 36.0 ],
									"text" : "Text alignment (horizontal and vertical):"
								}

							}
, 							{
								"box" : 								{
									"attr" : "textvalign",
									"id" : "obj-16",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 370.5, 214.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "texthalign",
									"id" : "obj-14",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 344.0, 214.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 106.5, 539.0, 36.0 ],
									"text" : "A certain number of \"cards\", containing an icon, a text (name), and possibly a value, can be placed and moved around a plane",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "cardborder",
									"id" : "obj-9",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 555.0, 468.0, 150.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.0, 154.0, 43.0, 23.0 ],
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"autofit" : 1,
									"id" : "obj-69",
									"ignoreclick" : 1,
									"maxclass" : "fpic",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "jit_matrix" ],
									"patching_rect" : [ 218.5, 475.0, 83.0, 86.0 ],
									"pic" : "musicstand.png",
									"presentation" : 1,
									"presentation_rect" : [ 544.0, 339.0, 83.0, 86.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.901796, 0.956763, 0.776819, 1.0 ],
									"cardbordercolor" : [ 0.501961, 0.501961, 0.501961, 0.43 ],
									"center" : [ 12.722308, -109.372269000000003 ],
									"gridcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"hint" : "Ctrl+Click & Drag on the icons to change their gain",
									"id" : "obj-1",
									"maxclass" : "dada.stage",
									"maximum" : 12.0,
									"minimum" : -90.0,
									"numdigits" : 0,
									"numinlets" : 2,
									"numoutlets" : 3,
									"out" : "nn",
									"outlettype" : [ "", "", "bang" ],
									"patching_rect" : [ 16.0, 192.75, 527.0, 325.5 ],
									"presentation" : 1,
									"presentation_rect" : [ 271.0, 77.0, 613.0, 335.0 ],
									"showgrid" : 1,
									"slope" : 0.5,
									"stage_data_0000000000" : [ "stage", "[", "cards", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225419776, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079853056, "]", "[", "name", "2Fl", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Fl.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077215232, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079869440, "]", "[", "name", "2Ob", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Ob.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225485312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080459264, "]", "[", "name", "2ClBb", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Cl.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077018624, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080451072, "]", "[", "name", "2Bn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Bn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227402240, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080926208, "]", "[", "name", "2Hn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Hn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223977984, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080934400, "]", "[", "name", "2TpC", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Tp.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227787264, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223453696, "]", "[", "name", "2Vn", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Vn.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3221225472, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078460416, "]", "[", "name", "1Va", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Va.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080049664, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, "]", "[", "name", "1Vc", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Vc.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "[", "[", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080492032, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223977984, "]", "[", "name", "1Cb", "]", "[", "value", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "]", "[", "icon", "Cb.png", "]", "[", "height", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078689792, "]", "[", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3220176896, "]", "]", "]" ],
									"stage_data_count" : [ 1 ],
									"versionnumber" : 40000
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.stage", 80 ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 583.0, 112.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"source" : [ "obj-1", 0 ]
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
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-31", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "GreenTextButtons",
								"parentstyle" : "RedTextButtons",
								"multi" : 0
							}
, 							{
								"name" : "RedTextButtons",
								"default" : 								{
									"accentcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
									"bgcolor" : [ 0.827321, 0.874747, 0.7195, 1.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"elementcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontname" : [ "Helvetica" ],
									"selectioncolor" : [ 0.1, 0.1, 0.1, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 10.0, 85.0, 50.0, 22.0 ],
					"saved_object_attributes" : 					{
						"fontsize" : 13.0
					}
,
					"text" : "p basic",
					"varname" : "basic_tab"
				}

			}
, 			{
				"box" : 				{
					"border" : 0,
					"filename" : "helpname.js",
					"id" : "obj-4",
					"ignoreclick" : 1,
					"jsarguments" : [ "dada.stage" ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 10.0, 229.587997000000001, 57.567627000000002 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 809.0, 607.0 ],
						"default_fontsize" : 13.0,
						"gridsize" : [ 5.0, 5.0 ],
						"showontab" : 1,
						"boxes" : [  ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 205.0, 205.0, 50.0, 22.0 ],
					"saved_object_attributes" : 					{
						"fontsize" : 13.0
					}
,
					"text" : "p ?",
					"varname" : "q_tab"
				}

			}
 ],
		"lines" : [  ],
		"parameters" : 		{
			"obj-15::obj-7::obj-8::obj-54" : [ "slider", "slider", 0 ],
			"obj-15::obj-7::obj-8::obj-59" : [ "number", "number", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "bach.print.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.base.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.cartesian.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.commons.grid.maxpat",
				"bootpath" : "~/Documents/Max 8/Packages/dada/help",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "dada.commons.maxpat",
				"bootpath" : "~/Documents/Max 8/Packages/dada/help",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "dada.stage.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "helpdetails.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "helpname.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "helpstarter.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "musicstand.png",
				"bootpath" : "~/Documents/Max 8/Packages/dada/media/orchestra",
				"patcherrelativepath" : "../media/orchestra",
				"type" : "PNG",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
