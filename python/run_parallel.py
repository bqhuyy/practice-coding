import cv2
import torch
import json
import numpy as np
import os
import multiprocessing
from multiprocessing import Pool, Process
from pycocotools.coco import COCO
import matplotlib.pyplot as plt
from PIL import Image
from joblib import Parallel, delayed
import tqdm

def xywh2xyxy(bbox):
    return [bbox[0], bbox[1], bbox[0]+bbox[2], bbox[1]+bbox[3]]

def drawBBox(img, anns):
    for ann in anns:
        bbox = xywh2xyxy(ann['bbox'])
        img = cv2.rectangle(img, (int(bbox[0]), int(bbox[1])), (int(bbox[2]), int(bbox[3])), color=(0,0,255), thickness=4)

def process(coco_annotation, img_id, root_path, out_path):
    # Pick one image.
    img_info = coco_annotation.loadImgs([img_id])[0]
    img_file_name = img_info["file_name"]

    # Get all the annotations for the specified image.
    ann_ids = coco_annotation.getAnnIds(imgIds=[img_id], iscrowd=None)
    anns = coco_annotation.loadAnns(ann_ids)
    # print(f"Annotations for Image ID {img_id}:", anns)

    img = cv2.imread(os.path.join(root_path, img_file_name))
    drawBBox(img, anns)

    if not os.path.exists(out_path):
        os.makedirs(out_path)
    out_file_name = os.path.join(out_path, img_file_name)
    print(f"Output: {out_file_name}")
    cv2.imwrite(out_file_name, img)

def main(catIds=[]):
    dataset_name = 'test2019'
    root_path = f'/home/ubuntu/ssd/data/RPC/{dataset_name}'
    coco_annotation_file_path = f"/home/ubuntu/ssd/data/RPC/single_obj/instances_{dataset_name}.json"
    out_path = f'/home/ubuntu/ssd/data/RPC/vis/{dataset_name}'

    coco_annotation = COCO(annotation_file=coco_annotation_file_path)

    # Category IDs.
    if len(catIds) == 0:
        cat_ids = coco_annotation.getCatIds()
        print(f"Number of Unique Categories: {len(cat_ids)}")
        print("Category IDs:", cat_ids)  # The IDs are not necessarily consecutive.

    # All categories.
    cats = coco_annotation.loadCats(cat_ids)
    cat_names = [cat["name"] for cat in cats]
    print("Categories Names:", cat_names)

    # Get the ID of all the images containing the object of the category.
    img_ids = coco_annotation.getImgIds(catIds=cat_ids)
    print("Number of Images:", len(img_ids))

    print("Number of cpu : ", multiprocessing.cpu_count())

    # Sequence process
    # procs = []
    # # instantiating process with arguments
    # for img_id in img_ids:
    #     print(f"Start {img_id}...")
    #     proc = Process(target=process, args=(coco_annotation, img_id, root_path, out_path))
    #     procs.append(proc)

    # # complete the processes
    # for proc in procs:
    #     proc.join()

    # Parallel process with joblib
    Parallel(n_jobs=8)(delayed(process)(coco_annotation, img_id, root_path, out_path) for img_id in img_ids)

if __name__ == "__main__":
    main()